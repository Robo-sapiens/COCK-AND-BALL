//
// Created by kira on 04.09.2020.
//

#include "abstract_service.h"

AbstractService::AbstractService(const std::string &node_name, const rclcpp::NodeOptions &options)
    : Node(node_name, options) {}
