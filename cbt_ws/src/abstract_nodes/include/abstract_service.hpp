//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_HPP_

#include "abstract_node.h"

template<class ServiceT>
class AbstractService : public AbstractNode {
 public:
    AbstractService(AbstractNodeDescription::SharedPtr description,
                    rclcpp::executor::Executor::SharedPtr executor,
                    CBType cb_group_type)
        : AbstractNode(description, executor, cb_group_type) {}

 protected:
    virtual void callback(std::shared_ptr<typename ServiceT::Request> request,
                          std::shared_ptr<typename ServiceT::Response> response) = 0;

    typename rclcpp::Service<ServiceT>::SharedPtr _service{_node->create_service<ServiceT>(
        _description->server_name(),
        [this](std::shared_ptr<rmw_request_id_t> request_header,
               std::shared_ptr<typename ServiceT::Request> request,
               std::shared_ptr<typename ServiceT::Response> response) {
            (void) request_header;
            callback(request, response);
        },
        _service_qos_profile,
        _cb_group)
    };
};

#endif  // COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_HPP_
