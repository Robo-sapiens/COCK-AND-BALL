//
// Created by kira on 04.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_DESCRIPTION_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_DESCRIPTION_H_

#include <string>
#include <memory>

using namespace std::string_literals;

class AbstractNodeDescription {
 public:
    using SharedPtr = std::shared_ptr<AbstractNodeDescription>;
    explicit AbstractNodeDescription(const std::string &client_user = std::string{});
    std::string client_name() const;
    std::string server_name() const;
    std::string qualified_name() const;
    virtual std::string name() const = 0;
 private:
    std::string _client_user;
};

#endif  // COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ABSTRACT_NODE_DESCRIPTION_H_
