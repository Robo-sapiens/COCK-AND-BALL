//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_CLIENT_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_CLIENT_HPP_

#include "abstract_node.h"
#include "abstract_request.hpp"

using namespace std::chrono_literals;

template<class ServiceT>
class AbstractServiceClient : public AbstractNode {
 public:
    using RequestCBType = typename rclcpp::Client<ServiceT>::CallbackType;
    using RequestSharedPtr = typename AbstractRequest<typename ServiceT::Request>::SharedPtr;
    using SharedFuture = typename rclcpp::Client<ServiceT>::SharedFuture;

    AbstractServiceClient(AbstractNodeDescription::SharedPtr description,
                          rclcpp::executor::Executor::SharedPtr executor,
                          CBType cb_group_type)
        : AbstractNode(description, executor, cb_group_type) {}
    SharedFuture request(RequestSharedPtr request_shared_ptr, RequestCBType cb = {}) {
        for (int i = 0; i < Constants::RetryTimes; ++i) {
            if (_client->wait_for_service(100ms)) {
                break;
            }
            debug("RECONNECTING");
        }
        if (!_client->service_is_ready()) {
            throw std::runtime_error("service is not ready");  // TODO: base exception and namespace
        }
        return _client->async_send_request(request_shared_ptr->impl(), cb);
//        auto future{_client->async_send_request(request, cb)};
//        return future;
//        while (true) {
//            if (future.wait_for(10ms) == std::future_status::ready) {
//                return future.get();
//            }
//        }
//    }
    }
 protected:
    typename rclcpp::Client<ServiceT>::SharedPtr _client{
        _node->create_client<ServiceT>(_description->server_name(), _service_qos_profile, _cb_group)
    };
};

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_SERVICE_CLIENT_HPP_
