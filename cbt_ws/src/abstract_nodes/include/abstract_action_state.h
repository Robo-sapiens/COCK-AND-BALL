//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_STATE_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_STATE_H_

#include "state_machine.h"

namespace cock_and_ball {
using namespace state_machine;
namespace abstract {
class IActionState : public IState {
 public:
 private:

};

class InitialState : public IActionState {
 public:
    std::string name() const override;
};

class WaitingCommandState : public IActionState {
 public:
    std::string name() const override;
};

class ExecutingState : public IActionState {
 public:
    std::string name() const override;
};

class SuccessState : public IActionState {
 public:
    std::string name() const override;
};

class FailState : public IActionState {
 public:
    std::string name() const override;
};

class ErrorState : public IActionState {
 public:
    std::string name() const override;
};
}  // namespace abstract
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_STATE_H_
