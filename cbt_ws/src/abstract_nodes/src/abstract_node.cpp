//
// Created by kira on 04.09.2020.
//

#include "abstract_node.h"

namespace cock_and_ball {
namespace abstract {
AbstractNode::AbstractNode(AbstractNodeDescription::SharedPtr description,
                           executor::RobotExecutor::SharedPtr executor,
                           AbstractNode::CBGrType cb_group_type)
    : _node(new rclcpp::Node(description->qualified_name())),
      _description(description),
      _executor(executor) {
    _cb_group = _node->create_callback_group(cb_group_type);
    _executor.lock()->get()->add_node(_node);
}
void AbstractNode::debug(const std::string &log_str) const {
    RCLCPP_DEBUG(_node->get_logger(), log_str);
}
void AbstractNode::info(const std::string &log_str) const {
    RCLCPP_INFO(_node->get_logger(), log_str);
}
void AbstractNode::warn(const std::string &log_str) const {
    RCLCPP_WARN(_node->get_logger(), log_str);
}
void AbstractNode::error(const std::string &log_str) const {
    RCLCPP_ERROR(_node->get_logger(), log_str);
}
rclcpp::Logger AbstractNode::logger() const {
    return _node->get_logger();
}
}  // namespace abstract
}  // namespace cock_and_ball
