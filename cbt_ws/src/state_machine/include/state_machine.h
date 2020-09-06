//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_H_
#define COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_H_

#include "cock_and_ball_exception.h"

#include <memory>
#include <map>
#include <regex>
#include <unordered_map>

namespace cock_and_ball {
namespace state_machine {
class StateException : public Exception {
 public:
    explicit StateException(const std::string &what);
};

class IState {
 public:
    using SharedPtr = std::shared_ptr<IState>;
    [[nodiscard]] virtual std::string name() const = 0;
};

class StateCollection {
 public:
    StateCollection(std::initializer_list<IState::SharedPtr> &&states);
    [[nodiscard]] IState::SharedPtr get_one(const std::string &name) const;
    [[nodiscard]] std::vector<IState::SharedPtr> get(const std::regex &state_regex) const;
 private:
    std::map<std::string, IState::SharedPtr> _name_to_state{};
};

class StateTransitions {
 public:
    using UniquePtr = std::unique_ptr<StateTransitions>;

    struct Transition {
        IState::SharedPtr src;
        IState::SharedPtr dst;
    };
    using MultiMap = std::unordered_multimap<std::string, Transition>;

    explicit StateTransitions(MultiMap &&transitions, StateCollection &&collection);

    void add_transition(const std::string &trigger, Transition transition);
    [[nodiscard]] IState::SharedPtr next_state(const IState::SharedPtr &src,
                                               const std::string &trigger) const;
    void extend_with(const std::string &trigger,
                     const std::regex &src_regex,
                     const IState::SharedPtr &dst);

 private:
    MultiMap _transitions;
    StateCollection _collection;
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
}  // namespace state_machine
}  // namespace cock_and_ball

#endif // COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_STATE_MACHINE_H_
