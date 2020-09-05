//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_H_

#include "abstract_node_description.h"
#include "robot_executor.h"

#include <rclcpp/node.hpp>
#include <rclcpp/executors.hpp>

namespace cock_and_ball {
namespace Constants {
constexpr short RetryTimes{100};
}  // constants

class AbstractNode {
 public:
    using SharedPtr = std::shared_ptr<AbstractNode>;
    using CBGrType = rclcpp::callback_group::CallbackGroupType;

    AbstractNode() = delete;
    AbstractNode(AbstractNodeDescription::SharedPtr description, RobotExecutor::SharedPtr executor,
                 CBGrType cb_group_type = CBGrType::MutuallyExclusive);

    [[nodiscard]] rclcpp::Logger logger() const;
    void debug(const std::string &log_str) const;
    void info(const std::string &log_str) const;
    void warn(const std::string &log_str) const;
    void error(const std::string &log_str) const;

 protected:
    rclcpp::Node::SharedPtr _node;
    AbstractNodeDescription::SharedPtr _description;
    RobotExecutor::WeakPtr _executor;
    rmw_qos_profile_t _service_qos_profile = rmw_qos_profile_services_default;
    rclcpp::callback_group::CallbackGroup::SharedPtr _cb_group;
};
}  // namespace cock_and_ball

#endif  // COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_H_
