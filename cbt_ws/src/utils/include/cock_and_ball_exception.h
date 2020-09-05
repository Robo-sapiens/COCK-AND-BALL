//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_COCK_AND_BALL_EXCEPTION_H_
#define COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_COCK_AND_BALL_EXCEPTION_H_

#include <exception>
#include <string>

namespace cock_and_ball {
class Exception : public std::exception {
 public:
    explicit Exception(const std::string &what);
    const char *what() const noexcept override;
 private:
    std::string _what;
};
}  // namespace cock_and_ball

#endif // COCK_AND_BALL_CBT_WS_SRC_UTILS_INCLUDE_COCK_AND_BALL_EXCEPTION_H_
