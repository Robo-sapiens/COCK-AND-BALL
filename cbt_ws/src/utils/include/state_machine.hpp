//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_HPP_

#include "cock_and_ball_exception.h"

#include <memory>

namespace cock_and_ball {
template<class StateT> // should have machine
class StateMachine {
 public:
    StateMachine() = default;
    [[nodiscard]] StateT &current() const {
        if (!_current_state) {
            throw Exception{"firstly initialize the state"};
        }
        return *_current_state;
    }
    void set_current_state(std::unique_ptr<StateT> &&state) {
        _current_state = std::move(state);
    }

 private:
    typename std::shared_ptr<StateT> _current_state{nullptr};
};
}  // namespace cock_and_ball

#endif // COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_HPP_
