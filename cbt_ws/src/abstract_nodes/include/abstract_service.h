//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_H_

#include <rclcpp/rclcpp.hpp>

using rclcpp::Node;

class AbstractService : public Node {
 public:
    AbstractService(const std::string &node_name, const rclcpp::NodeOptions &options);

 private:
};

#endif  // COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_H_
