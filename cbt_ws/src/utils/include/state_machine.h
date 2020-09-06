//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_H_
#define COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_H_

#include "cock_and_ball_exception.h"

#include <memory>
#include <unordered_map>

namespace cock_and_ball {
class StateException : public Exception {
 public:
    explicit StateException(const std::string &what);
};

class IState {
 public:
    using SharedPtr = std::shared_ptr<IState>;
    [[nodiscard]] virtual std::string name() const = 0;
};

class StateTransitions {
 public:
    using UniquePtr = std::unique_ptr<StateTransitions>;

    struct Transition {
        IState::SharedPtr src;
        IState::SharedPtr dst;
    };
    using MultiMap = std::unordered_multimap<std::string, Transition>;

    explicit StateTransitions(MultiMap &&transitions);

    void add_transition(const std::string &trigger, Transition transition);
    [[nodiscard]] IState::SharedPtr next_state(const IState::SharedPtr &src,
                                               const std::string &trigger) const;

 private:
    MultiMap _transitions;
};

class StateMachine {
 public:
    StateMachine() = delete;
    explicit StateMachine(IState::SharedPtr initial_state,
                          StateTransitions::UniquePtr &&transitions);

    [[nodiscard]] IState::SharedPtr current() const;
    void change_state(const std::string &trigger);

 private:
    void set_current_state(IState::SharedPtr state);

    IState::SharedPtr _current_state;
    StateTransitions::UniquePtr _transitions;
};
}  // namespace cock_and_ball

#endif // COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_H_
