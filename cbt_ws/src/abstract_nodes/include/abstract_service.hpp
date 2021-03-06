//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_HPP_

#include "abstract_node.h"

namespace cock_and_ball {
namespace abstract {
template<class ServiceT>
class AbstractService : public AbstractNode {
 public:
    AbstractService(AbstractNodeDescription::SharedPtr description,
                    executor::RobotExecutor::SharedPtr executor,
                    CBGrType cb_group_type)
        : AbstractNode(description, executor, cb_group_type) {}

 protected:
    virtual void callback(std::shared_ptr<typename ServiceT::Request> request,
                          std::shared_ptr<typename ServiceT::Response> response) = 0;

    typename rclcpp::Service<ServiceT>::SharedPtr _service{_node->create_service<ServiceT>(
        _description->name(),
        [this](std::shared_ptr<rmw_request_id_t> request_header,
               std::shared_ptr<typename ServiceT::Request> request,
               std::shared_ptr<typename ServiceT::Response> response) {
            (void) request_header;
            executor::Job job{_executor.lock()};
            callback(request, response);
        },
        _service_qos_profile,
        _cb_group)
    };
};
}  // namespace abstract
}  // namespace cock_and_ball

#endif  // COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_HPP_
