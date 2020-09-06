//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_

#include "abstract_node.h"
#include "state_machine.h"

#include <rclcpp_action/rclcpp_action.hpp>

namespace cock_and_ball {
namespace abstract {
template<class ActionT>
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
                info("Received goal request with order %d", goal->order);
                (void) uuid;
                return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
            },
            [this](GoalHandleSharedPtr goal_handle) {
                (void) goal_handle;
                info("Received request to cancel goal");
                return rclcpp_action::CancelResponse::ACCEPT;
            },
            [this](GoalHandleSharedPtr goal_handle) {
                (void) goal_handle;
                std::thread{[this]() { execute(); }}.detach(); // TASK?
            },
            rcl_action_server_get_default_options(),
            _cb_group
        )
    };

    void execute(GoalHandleSharedPtr goal_handle) {
        info("Executing goal");
        rclcpp::Rate loop_rate(1);
        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<typename ActionT::Feedback>();
        auto &sequence = feedback->sequence;
        sequence.push_back(0);
        sequence.push_back(1);
        auto result = std::make_shared<typename ActionT::Result>();

        for (int i = 1; (i < goal->order) && rclcpp::ok(); ++i) {
            // Check if there is a cancel request
            if (goal_handle->is_canceling()) {
                result->sequence = sequence;
                goal_handle->canceled(result);
                info("Goal Canceled");
                return;
            }
            // Update sequence
            sequence.push_back(sequence[i] + sequence[i - 1]);
            // Publish feedback
            goal_handle->publish_feedback(feedback);
            info("Publish Feedback");

            loop_rate.sleep();
        }

        // Check if goal is done
        if (rclcpp::ok()) {
            result->sequence = sequence;
            goal_handle->succeed(result);
            info("Goal Succeeded");
        }
    }
};
}  // namespace abstract
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_
