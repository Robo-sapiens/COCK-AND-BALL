cmake_minimum_required(VERSION 3.5)
project(state_machine)

find_package(ament_cmake REQUIRED)

add_library(state_machine SHARED
        src/state_machine.cpp)

target_link_libraries(state_machine PUBLIC
        utils)

target_include_directories(state_machine PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${rclcpp_INCLUDE_DIRS})

install(TARGETS state_machine
        EXPORT export_${PROJECT_NAME}
        DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

add_executable(example_state_machine example/example_state_machine.cpp)
target_link_libraries(example_state_machine PUBLIC state_machine)
