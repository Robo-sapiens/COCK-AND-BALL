//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_

#include "abstract_node.h"
#include "abstract_action_state.hpp"
#include "state_machine.h"

#include <rclcpp_action/rclcpp_action.hpp>

namespace cock_and_ball {
namespace abstract {
template<class ActionT,
    class Goal = typename ActionT::Goal,
    class Result = typename ActionT::Result,
    class Feedback = typename ActionT::Feedback>
class AbstractActionServer : public AbstractNode {
 public:
    using GoalHandle = rclcpp_action::ServerGoalHandle<ActionT>;
    using GoalHandleSharedPtr = std::shared_ptr<GoalHandle>;

    AbstractActionServer(AbstractNodeDescription::SharedPtr description,
                         executor::RobotExecutor::SharedPtr executor,
                         CBGrType cb_group_type)
        : AbstractNode(description, executor, cb_group_type) {}

 protected:
    typename rclcpp_action::Server<ActionT>::SharedPtr _server{
        rclcpp_action::create_server<ActionT>(
            _node,
            _description->name(),
            [this](const rclcpp_action::GoalUUID &uuid,
                   std::shared_ptr<typename ActionT::Goal> goal) {
                executor::Job job{_executor.lock()};
                debug({uuid.begin(), uuid.end()});
                info("Received goal request" + goal->repr());
                if (_machine.current()->name() == "WaitingCommand") {
                    return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
                }
                return rclcpp_action::GoalResponse::REJECT;
            },
            [this](GoalHandleSharedPtr goal_handle) {
                (void) goal_handle;
                executor::Job job{_executor.lock()};
                info("Received request to cancel goal");
                if (std::regex_match(_machine.current()->name(), std::regex{".*Executing.*"})) {
                    _trigger_q->emit("cancel");
                    return rclcpp_action::CancelResponse::ACCEPT;
                }
                return rclcpp_action::CancelResponse::REJECT;
            },
            [this](GoalHandleSharedPtr goal_handle) {
                executor::Job job{_executor.lock()};
                _current_task.join();
                _current_task = std::thread{[this, &goal_handle]() { execute(goal_handle); }}; // TASK?
            },
            rcl_action_server_get_default_options(),
            _cb_group
        )
    };

    void execute(GoalHandleSharedPtr goal_handle) {
        executor::Job job{_executor.lock()};
        info("Executing goal");
        _goal_q->emit(goal_handle->get_goal());
        _machine.change_state("execute");
        while (not _result_q->ready()) {
            auto *current = dynamic_cast<IActionState<ActionT> *>(_machine.current().get());
            current->execute();
        }
        auto result = _result_q.dispatch_signal();
        goal_handle->succeed(result);
    }

 protected:
    typename IActionState<ActionT>::TriggerQ _trigger_q;
    typename IActionState<ActionT>::GoalQ _goal_q;
    typename IActionState<ActionT>::ResultQ _result_q;
    typename IActionState<ActionT>::FeedbackQ _fb_q;
    state_machine::StateMachine _machine;
    std::thread _current_task;
};
}  // namespace abstract
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_
