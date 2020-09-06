//
// Created by kira on 05.09.2020.
//

#include "abstract_action_state.h"

namespace cock_and_ball {
namespace abstract {
std::string InitialState::name() const {
    return "Initial";
}
std::string WaitingCommandState::name() const {
    return "WaitingCommand";
}
std::string ExecutingState::name() const {
    return "Executing";
}
std::string SuccessState::name() const {
    return "Success";
}
std::string FailState::name() const {
    return "Fail";
}
std::string ErrorState::name() const {
    return "Error";
}
}  // namespace abstract
}  // namespace cock_and_ball
