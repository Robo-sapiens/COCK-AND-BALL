cmake_minimum_required(VERSION 3.5)
project(abstract_nodes)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
# TODO required abstract_nodes check

add_library(abstract_nodes SHARED
        src/abstract_node.cpp
        src/abstract_node_description.cpp
        include/abstract_service.hpp
        include/abstract_service_client.hpp
        include/abstract_request.hpp
        include/abstract_action_server.hpp
        )

target_link_libraries(abstract_nodes PUBLIC
        ${rclcpp_LIBRARIES})
target_include_directories(abstract_nodes PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${rclcpp_INCLUDE_DIRS})

install(TARGETS abstract_nodes
        EXPORT export_${PROJECT_NAME}
        DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

add_executable(example_abstract_service example/example_abstract_srvcli.cpp)
target_link_libraries(example_abstract_service PUBLIC abstract_nodes
        ${example_interfaces_LIBRARIES})
add_executable(example_abstract_action example/example_abstract_action.cpp)
target_link_libraries(example_abstract_action PUBLIC abstract_nodes
        ${example_interfaces_LIBRARIES})
