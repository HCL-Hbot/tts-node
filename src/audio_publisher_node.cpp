#include <rclcpp/rclcpp.hpp>

#include "audio_tools/msg/audio_data.hpp"
#include "audio_tools/msg/audio_data_stamped.hpp"
#include "audio_tools/msg/audio_info.hpp"
#include <std_msgs/msg/header.hpp>

#include <chrono>
#include <iostream>
#include <vector>

using namespace std::chrono_literals;

class TTSPublisher : public rclcpp::Node {
public:
  TTSPublisher() : Node("tts_publisher_node") {

    publisher_ = this->create_publisher<audio_tools::msg::AudioDataStamped>(
        "tts_samples", 1);
    timer_ = this->create_wall_timer(
        10ms, std::bind(&TTSPublisher::timer_callback, this));
    std::cin.sync_with_stdio(false); // Disable sync for faster I/O
  }

private:
  void timer_callback() {
    std::vector<uint8_t> buffer(2048);
    std::cin.read(reinterpret_cast<char *>(buffer.data()), buffer.size());
    std::streamsize bytes_read = std::cin.gcount();

    if (bytes_read <= 0) {
      rclcpp::shutdown();
      return;
    }

    auto msg = audio_tools::msg::AudioDataStamped();
    msg.header.stamp = this->get_clock()->now();

    msg.audio.data.assign(buffer.begin(), buffer.begin() + bytes_read);

    msg.info.channels = 1;
    msg.info.sample_rate = 22050;
    msg.info.sample_format = "S16LE";

    publisher_->publish(msg);
  }

  rclcpp::Publisher<audio_tools::msg::AudioDataStamped>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TTSPublisher>());
  rclcpp::shutdown();
  return 0;
}
