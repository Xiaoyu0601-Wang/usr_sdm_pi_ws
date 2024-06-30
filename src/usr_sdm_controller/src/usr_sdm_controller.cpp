#include <chrono>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "usr_sdm_controller/can_protocol.hpp"

using namespace std::chrono_literals;

class USRSDM : public rclcpp::Node
{
  public:
    USRSDM()
    : Node("usr_sdm_controller")
    , count_(0)
    {
    	can.reset(new amp::usrsdm::CANProtocol);
    	can->interfaceSetup();

    	publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    	timer_ = this->create_wall_timer(2000ms, std::bind(&USRSDM::timer_callback, this));
    }

  private:
    void timer_callback()
    {
    	RCLCPP_INFO(this->get_logger(), "Publishing");
//      auto message = std_msgs::msg::String();
//      message.data = "Hello, world! " + std::to_string(count_++);
//      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
//      publisher_->publish(message);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;

//    amp::usrsdm::CANProtocol can;
    amp::usrsdm::CANProtocol::Ptr can;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<USRSDM>());
  rclcpp::shutdown();
  return 0;
}
