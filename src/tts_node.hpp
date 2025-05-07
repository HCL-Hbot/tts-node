#ifndef TTS_NODE_HPP
#define TTS_NODE_HPP

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TTSNode : public rclcpp::Node {
public:
  TTSNode();

private:
  void text_callback(const std_msgs::msg::String::SharedPtr msg);
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  std::string speak_script_path_;
  std::string to_speak_path_;
  std::string model_path_;
  std::string model_config_path_;
};


#endif /* TTS_NODE_HPP */