//
// Created by kira on 04.09.2020.
//

#include "abstract_node_description.h"

AbstractNodeDescription::AbstractNodeDescription(const std::string &client_user)
    : _client_user(client_user) {}
std::string AbstractNodeDescription::client_name() const {
    return _client_user + "_" + name() + "_client";
}
std::string AbstractNodeDescription::server_name() const {
    return name() + "_server";
}
std::string AbstractNodeDescription::qualified_name() const {
    if (!_client_user.empty()) {
        return client_name();
    }
    return server_name();
}
