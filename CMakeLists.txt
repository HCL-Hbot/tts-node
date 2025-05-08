cmake_minimum_required(VERSION 3.1...3.14)
project(tts C CXX)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(builtin_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(std_msgs REQUIRED)
find_package(audio_tools REQUIRED)


add_executable(tts_node src/tts_node.cpp)

ament_target_dependencies(tts_node
   rclcpp
   std_msgs
)
target_link_libraries(tts_node "${cpp_typesupport_target}")

add_executable(tts_publisher_node src/audio_publisher_node.cpp)
ament_target_dependencies(tts_publisher_node
   rclcpp
   std_msgs
   audio_tools
)
target_link_libraries(tts_publisher_node "${cpp_typesupport_target}")



if(UNIX AND NOT APPLE)  # Linux only
 target_compile_options(tts_node PRIVATE -Wall)
endif()

install(TARGETS
tts_node tts_publisher_node
DESTINATION lib/${PROJECT_NAME}) 

ament_package()
