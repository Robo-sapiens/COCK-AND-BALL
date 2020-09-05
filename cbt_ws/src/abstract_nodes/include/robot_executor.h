//
// Created by kira on 05.09.2020.
//

#ifndef COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ROBOT_EXECUTOR_H_
#define COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ROBOT_EXECUTOR_H_

#include <rclcpp/executors/single_threaded_executor.hpp>
using namespace std::chrono_literals;


class RobotExecutor {
 public:
    friend class Job;
    using SharedPtr = std::shared_ptr<RobotExecutor>;
    using WeakPtr = std::weak_ptr<RobotExecutor>;

    explicit RobotExecutor(const rclcpp::executor::ExecutorArgs & args = rclcpp::executor::ExecutorArgs{});
    ~RobotExecutor();

    [[nodiscard]] rclcpp::executors::SingleThreadedExecutor::SharedPtr get() const;
 private:
    std::atomic<size_t> _amount_of_jobs{1};
    rclcpp::executors::SingleThreadedExecutor::SharedPtr _single_threaded_executor;
    std::thread _worker_thread{[this]() {
        while (_amount_of_jobs != 0) {
            _single_threaded_executor->spin_once();
        }
        std::cout << "finished" << std::endl;
    }};
};

class Job {
 public:
    explicit Job(RobotExecutor::SharedPtr executor);
    ~Job();
 private:
    RobotExecutor::WeakPtr _executor;
};

#endif //COCK_AND_BALL_CBT_WS_SRC_ABSTRACT_NODES_INCLUDE_ROBOT_EXECUTOR_H_
