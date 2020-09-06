//
// Created by kira on 05.09.2020.
//

#include "abstract_node_exception.h"

namespace cock_and_ball {
namespace abstract {
AbstractNodeException::AbstractNodeException(const std::string &what) : Exception(what) {}
}  // namespace abstract
}  // namespace cock_and_ball
