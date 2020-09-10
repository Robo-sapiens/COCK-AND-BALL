//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_STATE_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_STATE_H_

#include "state_machine.h"

namespace cock_and_ball {
using namespace state_machine;
using namespace signal;
namespace abstract {
template<class ActionT,
    class Goal = typename ActionT::Goal,
    class Result = typename ActionT::Result,
    class Feedback = typename ActionT::Feedback>
class IActionState : public IState {
 public:
    using TriggerQ = SignalQueue<std::string>::SharedPtr;
    using GoalQ = typename SignalQueue<typename Goal::ConstSharedPtr const>::SharedPtr;
    using ResultQ = typename SignalQueue<typename Result::SharedPtr>::SharedPtr;
    using FeedbackQ = typename SignalQueue<typename Feedback::SharedPtr>::SharedPtr;

    explicit IActionState(TriggerQ trigger_q,
                          GoalQ goal_q,
                          ResultQ result_q,
                          FeedbackQ fb_q)
        : _trigger_q(std::move(trigger_q)),
          _goal_q(std::move(goal_q)),
          _result_q(std::move(result_q)),
          _fb_q(std::move(fb_q)) {}

    virtual void execute() = 0;
 protected:
    TriggerQ _trigger_q;
    GoalQ _goal_q;
    ResultQ _result_q;
    FeedbackQ _fb_q;
};

template<class ActionT>
class InitialState : public IActionState<ActionT> {
 public:
    std::string name() const override {
        return "Initial";
    }
};

template<class ActionT>
class WaitingCommandState : public IActionState<ActionT> {
 public:
    std::string name() const override {
        return "WaitingCommand";
    }
};

template<class ActionT>
class ExecutingState : public IActionState<ActionT> {
 public:
    std::string name() const override {
        return "Executing";
    }
};

template<class ActionT>
class SuccessState : public IActionState<ActionT> {
 public:
    std::string name() const override {
        return "Success";
    }
};

template<class ActionT>
class FailState : public IActionState<ActionT> {
 public:
    std::string name() const override {
        return "Fail";
    }
};

template<class ActionT>
class ErrorState : public IActionState<ActionT> {
 public:
    std::string name() const override {
        return "Error";
    }
};
}  // namespace abstract
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_STATE_H_
