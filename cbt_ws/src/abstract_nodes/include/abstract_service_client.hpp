//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_CLIENT_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_CLIENT_HPP_

#include "abstract_node.h"
#include "abstract_request.hpp"
#include "abstract_node_exception.h"


namespace cock_and_ball {
namespace abstract {
template<class ServiceT>
class AbstractServiceClient : public AbstractNode {
 public:
    using RequestCBType = typename rclcpp::Client<ServiceT>::CallbackType;
    using RequestSharedPtr = typename AbstractRequest<typename ServiceT::Request>::SharedPtr;
    using ResponseSharedPtr = typename ServiceT::Response::SharedPtr;
    using SharedFuture = typename rclcpp::Client<ServiceT>::SharedFuture;

    AbstractServiceClient(AbstractNodeDescription::SharedPtr description,
                          executor::RobotExecutor::SharedPtr executor,
                          CBGrType cb_group_type)
        : AbstractNode(description, executor, cb_group_type) {}
    ResponseSharedPtr request(RequestSharedPtr request_shared_ptr, RequestCBType cb =
    [](SharedFuture future) { (void) future; }) {
        executor::Job job{_executor.lock()};
        wait_for_server();
        auto future{_client->async_send_request(request_shared_ptr->impl(), cb)};
        future.wait();
        return future.get();
    }
 private:
    void wait_for_server() const {
        for (int i = 0; i < Constants::RetryTimes; ++i) {
            if (_client->wait_for_service(Constants::WaitForServerTimeOut)) {
                break;
            }
            debug("RECONNECTING");
        }
        if (!_client->service_is_ready()) {
            throw AbstractNodeException("service is not ready");
        }
    }
 protected:
    typename rclcpp::Client<ServiceT>::SharedPtr _client{
        _node->create_client<ServiceT>(_description->name(), _service_qos_profile, _cb_group)
    };
};
}  // namespace abstract
}  // namespace cock_and_ball

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_CLIENT_HPP_
