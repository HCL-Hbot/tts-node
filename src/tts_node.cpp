#include "tts_node.hpp"
#include <cstdlib>  // for std::system
#include <string>
#include <fstream>

bool speak_with_file(const std::string & command, const std::string & text, const std::string & path, const std::string &model, std::string &model_config, int voice_id)
{
    std::ofstream speak_file(path.c_str());
    if (speak_file.fail()) {
        fprintf(stderr, "%s: failed to open speak_file\n", __func__);
        return false;
    } else {
        speak_file.write(text.c_str(), text.size());
        speak_file.close();
        int ret = system((command + " " + std::to_string(voice_id) + " " + path + " " + model + " " + model_config).c_str());
        if (ret != 0) {
            fprintf(stderr, "%s: failed to speak\n", __func__);
            return false;
        }
    }
    return true;
}

TTSNode::TTSNode() : Node("tts_node") {
  RCLCPP_INFO(this->get_logger(), "TTS Node has started.");
  this->declare_parameter<std::string>("speak_script_path", "src/speak_script.sh");
  this->declare_parameter<std::string>("to_speak_path", "src/tts_input.txt");
  this->declare_parameter<std::string>("model_path", "models/tts-model.onnx");
  this->declare_parameter<std::string>("model_config_path", "models/tts-model.onnx.json");

  this->get_parameter("speak_script_path", speak_script_path_);
  this->get_parameter("to_speak_path", to_speak_path_);
  this->get_parameter("model_path", model_path_);
  this->get_parameter("model_config_path", model_config_path_);
  subscription_ = this->create_subscription<std_msgs::msg::String>(
    "/tts_text", 10,
    std::bind(&TTSNode::text_callback, this, std::placeholders::_1)
  );
}

void TTSNode::text_callback(const std_msgs::msg::String::SharedPtr msg) {
  speak_with_file(speak_script_path_, msg->data, to_speak_path_, model_path_, model_config_path_, 2);
}

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TTSNode>());
  rclcpp::shutdown();
  return 0;
}
