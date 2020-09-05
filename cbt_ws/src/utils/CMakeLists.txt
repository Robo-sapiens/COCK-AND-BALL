cmake_minimum_required(VERSION 3.5)
project(utils)

# Default to C99
if (NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 99)
endif ()

# Default to C++14
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif ()

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_library(utils SHARED
        include/state_machine.hpp
        src/robot_executor.cpp
        src/cock_and_ball_exception.cpp
        )

target_link_libraries(utils PUBLIC
        ${rclcpp_LIBRARIES})

target_include_directories(utils PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${rclcpp_INCLUDE_DIRS})

install(TARGETS utils
        EXPORT export_${PROJECT_NAME}
        DESTINATION lib/${PROJECT_NAME})

if (BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    set(ament_cmake_copyright_FOUND TRUE)
    set(ament_cmake_cpplint_FOUND TRUE)
    ament_lint_auto_find_test_dependencies()
endif ()

ament_package()
add_executable(example_abstract_state example/example_state_machine.cpp)
target_link_libraries(example_abstract_state PUBLIC utils)
