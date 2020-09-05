//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_EXCEPTION_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_EXCEPTION_H_

#include "cock_and_ball_exception.h"

namespace cock_and_ball {
class AbstractNodeException : public Exception {
 public:
    AbstractNodeException(const std::string &what);
};
}  // cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_EXCEPTION_H_
