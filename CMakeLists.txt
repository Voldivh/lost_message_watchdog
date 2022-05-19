cmake_minimum_required(VERSION 3.8)
project(topic_monitor)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(topic_publisher src/topic_publisher.cc)
ament_target_dependencies(topic_publisher rclcpp std_msgs)

add_executable(topic_monitor src/topic_monitor.cc)
ament_target_dependencies(topic_monitor rclcpp std_msgs)

install(TARGETS
  topic_publisher
  topic_monitor
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
