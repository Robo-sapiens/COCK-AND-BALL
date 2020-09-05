//
// Created by kira on 05.09.2020.
//

#include "robot_executor.h"
RobotExecutor::RobotExecutor(const rclcpp::executor::ExecutorArgs &args)
    : _single_threaded_executor(std::make_shared<rclcpp::executors::SingleThreadedExecutor>(args)) {
}
RobotExecutor::~RobotExecutor() {
    --_amount_of_jobs;
    _worker_thread.join();
}
rclcpp::executors::SingleThreadedExecutor::SharedPtr RobotExecutor::get() const {
    return _single_threaded_executor;
}
Job::Job(RobotExecutor::SharedPtr executor) : _executor(executor) {
    ++_executor.lock()->_amount_of_jobs;
}
Job::~Job() {
    --_executor.lock()->_amount_of_jobs;
}
