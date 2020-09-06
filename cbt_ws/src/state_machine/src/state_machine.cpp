//
// Created by kira on 06.09.2020.
//

#include "state_machine.h"

#include <algorithm>

namespace cock_and_ball {
namespace state_machine {
StateException::StateException(const std::string &what) : Exception(what) {}
StateCollection::StateCollection(std::initializer_list<IState::SharedPtr> &&states) {
    for (const auto& state: states) {
        _name_to_state[state->name()] = state;
    }
}
IState::SharedPtr StateCollection::get_one(const std::string &name) const {
    return _name_to_state.at(name);
}
std::vector<IState::SharedPtr> StateCollection::get(const std::regex &state_regex) const {
    std::vector<IState::SharedPtr> states;
    for (const auto & [name, state]: _name_to_state) {
        if (std::regex_match(name, state_regex)) {
            states.push_back(state);
        }
    }
    return states;
}
StateTransitions::StateTransitions(MultiMap &&transitions, StateCollection &&collection)
    : _transitions(std::move(transitions)), _collection(std::move(collection)) {}
void StateTransitions::add_transition(const std::string &trigger, Transition transition) {
    _transitions.emplace(trigger, std::move(transition));
}
IState::SharedPtr StateTransitions::next_state(const IState::SharedPtr &src,
                                               const std::string &trigger) const {
    auto [range_begin, range_end] = _transitions.equal_range(trigger);
    auto dst_it = std::find_if(range_begin, range_end, [&src](const MultiMap::value_type &item) {
        return item.second.src == src;
    });
    if (dst_it != range_end) {
        return dst_it->second.dst;
    } else {
        throw StateException("can't change state from \"" + src->name() + "\" " +
            "with trigger \"" + trigger + "\"");
    }
}
void StateTransitions::extend_with(const std::string &trigger,
                                   const std::regex& src_regex,
                                   const IState::SharedPtr& dst) {
    for (const auto& src: _collection.get(src_regex)) {
        _transitions.emplace(trigger, Transition{src, dst});
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
}  // namespace state_machine
}  // namespace cock_and_ball
