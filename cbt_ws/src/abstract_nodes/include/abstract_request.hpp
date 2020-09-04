//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_REQUEST_HPP_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_REQUEST_HPP_

#include <memory>

namespace cock_and_ball {
template<class RequestT>
class AbstractRequest {
 public:
    using SharedPtr = std::shared_ptr<AbstractRequest<RequestT>>;

    AbstractRequest() = default;
    typename RequestT::SharedPtr impl() const {
        return _request;
    }
 protected:
    typename RequestT::SharedPtr _request{std::make_shared<RequestT>()};
};
}  // namespace cock_and_ball


#endif  // COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_REQUEST_HPP_
