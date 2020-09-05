//
// Created by kira on 05.09.2020.
//

#include "cock_and_ball_exception.h"

#include <cerrno>
#include <cstring>

namespace cock_and_ball {
Exception::Exception(const std::string &what)
    : _what("errno: " + std::to_string(errno) +
    "\nerror: " + std::strerror(errno) +
    "\nwhat: " + what) {}
const char *Exception::what() const noexcept {
    return _what.c_str();
}
}  // namespace cock_and_ball
