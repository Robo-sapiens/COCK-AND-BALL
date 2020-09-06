//
// Created by kira on 06.09.2020.
//

#include "state_machine.h"

#include <algorithm>

namespace cock_and_ball {
StateException::StateException(const std::string &what) : Exception(what) {}
StateTransitions::StateTransitions(MultiMap &&transitions)
    : _transitions(std::move(transitions)) {}
void StateTransitions::add_transition(const std::string &trigger, Transition transition) {
    _transitions.insert({trigger, transition});
}
IState::SharedPtr StateTransitions::next_state(const IState::SharedPtr &src,
                                               const std::string &trigger) const {
    auto range = _transitions.equal_range(trigger);
    auto dst_it = std::find_if(range.first, range.second, [&src](const MultiMap::value_type &item) {
        return item.second.src == src;
    });
    if (dst_it != range.second) {
        return dst_it->second.dst;
    } else {
        throw StateException("can't change state from \"" + src->name() + "\" " +
            "with trigger \"" + trigger + "\"");
    }
}
IState::SharedPtr StateMachine::current() const {
    return _current_state;
}
StateMachine::StateMachine(IState::SharedPtr initial_state,
                           StateTransitions::UniquePtr &&transitions)
    : _current_state(std::move(initial_state)), _transitions(std::move(transitions)) {}
void StateMachine::change_state(const std::string &trigger) {
    set_current_state(_transitions->next_state(_current_state, trigger));
}
void StateMachine::set_current_state(IState::SharedPtr state) {
    _current_state = std::move(state);
}
}  // namespace cock_and_ball
