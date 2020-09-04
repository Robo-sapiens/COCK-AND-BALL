//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_H_

#include "abstract_node_description.h"

#include <rclcpp/rclcpp.hpp>

namespace Constants {
    constexpr short RetryTimes{100};
}  // constants

class AbstractNode {
 public:
    using SharedPtr = std::shared_ptr<AbstractNode>;

    using CBType = rclcpp::callback_group::CallbackGroupType;
    AbstractNode(AbstractNodeDescription::SharedPtr description,
                 rclcpp::executor::Executor::SharedPtr executor,
                 CBType cb_group_type = CBType::MutuallyExclusive);

    rclcpp::Logger logger() const;
    void debug(const std::string &log_str) const;
    void info(const std::string &log_str) const;
    void warn(const std::string &log_str) const;
    void error(const std::string &log_str) const;

 protected:
    rclcpp::Node::SharedPtr _node;
    AbstractNodeDescription::SharedPtr _description;
    rclcpp::executor::Executor::SharedPtr _executor;
    rmw_qos_profile_t _service_qos_profile = rmw_qos_profile_services_default;
    rclcpp::callback_group::CallbackGroup::SharedPtr _cb_group;
};

#endif  // COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_H_
