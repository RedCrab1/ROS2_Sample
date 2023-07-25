#include "rclcpp/rclcpp.hpp"
#include <iostream>
#include "std_msgs/msg/string.hpp"
#include <string>

using namespace std;

using iString = std_msgs::msg::String;

class TimerSample: public rclcpp::Node{
        public:
                TimerSample(const string & node_name): Node(node_name)
                {
                        publisher_ = this->create_publisher<iString>("string_topic", 10);
                };
                virtual ~TimerSample(){};

                void Start()
                {
                        timer_ = this->create_wall_timer(1s, std::bind(&TimerSample::topictimer_callback, this));
                };

                void topictimer_callback()
                {
                        iString message;
                        message.data = "Hello world!";
                        publisher_->publish(message);
                };

        private:
                rclcpp::Publisher<iString>::SharedPtr publisher_;
                rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char ** argv)
{

  rclcpp::init(argc, argv);

  string name = "timer_sample";
  auto node_ = make_shared<TimerSample>(name);
  rclcpp::executors::SingleThreadedExecutor executor_;
  node_->Start();

  executor_.add_node(node_);
  executor_.spin();

  rclcpp::shutdown();
  return 0;
}

