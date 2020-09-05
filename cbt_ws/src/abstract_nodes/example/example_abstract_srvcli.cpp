//
// Created by kira on 04.09.2020.
//

#include "abstract_service.hpp"
#include "abstract_service_client.hpp"
#include "abstract_request.hpp"
#include "robot_executor.h"

#include <example_interfaces/srv/add_two_ints.hpp>

using example_interfaces::srv::AddTwoInts;
using namespace cock_and_ball;

class AddTwoIntsDescription : public AbstractNodeDescription {
 public:
    explicit AddTwoIntsDescription(const std::string &client_user = std::string{})
        : AbstractNodeDescription(client_user) {}
    std::string name() const override {
        return "AddTwoInts";
    }
};

class AddTwoIntsService : public AbstractService<AddTwoInts> {
 public:
    AddTwoIntsService(AbstractNodeDescription::SharedPtr description,
                      RobotExecutor::SharedPtr executor,
                      CBGrType cb_group_type)
        : AbstractService(description, executor, cb_group_type) {}
    void callback(std::shared_ptr<AddTwoInts::Request> request,
                  std::shared_ptr<AddTwoInts::Response> response) override {
        info("request: " + std::to_string(request->a) + " + " + std::to_string(request->b));
        response->sum = request->a + request->b;
    }
};

class AddTwoIntsClient : public AbstractServiceClient<AddTwoInts> {
 public:
    AddTwoIntsClient(AbstractNodeDescription::SharedPtr description,
                     RobotExecutor::SharedPtr executor,
                     CBGrType cb_group_type)
        : AbstractServiceClient(description, executor, cb_group_type) {}
};

class AddTwoIntsRequest : public AbstractRequest<AddTwoInts::Request> {
 public:
    AddTwoIntsRequest(long a, long b) {
        _request->a = a;
        _request->b = b;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);

    auto robot_executor = std::make_shared<RobotExecutor>();
    AddTwoIntsService service{
        std::make_shared<AddTwoIntsDescription>(),
        robot_executor,
        AbstractNode::CBGrType::MutuallyExclusive
    };
    AddTwoIntsClient client{
        std::make_shared<AddTwoIntsDescription>("me"),
        robot_executor,
        AbstractNode::CBGrType::MutuallyExclusive
    };
    auto result = client.request(std::make_shared<AddTwoIntsRequest>(10, 15));
    client.info(std::to_string(result->sum));
    client.info(std::to_string(client.request(std::make_shared<AddTwoIntsRequest>(1, 5))->sum));

    rclcpp::shutdown();
    return 0;
}
