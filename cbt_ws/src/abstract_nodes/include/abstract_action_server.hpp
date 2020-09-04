//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_

#include "abstract_node.h"

#include <rclcpp_action/rclcpp_action.hpp>

namespace cock_and_ball {
template<class ActionT>
class AbstractActionServer : public AbstractNode {
 public:
    AbstractActionServer(AbstractNodeDescription::SharedPtr description,
                         rclcpp::executor::Executor::SharedPtr executor,
                         CBGrType cb_group_type)
        : AbstractNode(description, executor, cb_group_type) {}

 protected:
//    typename rclcpp_action::Server<ActionT>::SharedPtr _server{
//        rclcpp_action::create_server<ActionT>(
//            _node,
//            _description->name(),
//
//        )
//    }
};
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_ACTION_SERVER_H_
