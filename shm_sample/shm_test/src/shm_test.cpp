#include <cstdio>
#include <rclcpp/rclcpp.hpp>
class PubNode : public rclcpp::Node
{
public:
	explicit PubNode(const std::string & node_name):Node(node_name)
	{
		using namespace std::chrono_literals;
		publisher_ = this->create_publisher<builtin_interfaces::msg::Time>(
			"current_time",
			rclcpp::SystemDefaultsQoS());
		auto topictimer_callback = 
			[&]()->void{
				auto loan_time_ = publisher_->borrow_loaned_message();
				loan_time_.get() = this->get_clock()->now();
				RCLCPP_INFO_STREAM(
					this->get_logger(),
					"pub: Current timestamp is: " <<
					std::to_string(loan_time_.get().sec) <<
					" seconds, " << std::to_string(loan_time_.get().nanosec) <<
					" nanoseconds.");
				publisher_->publish(std::move(loan_time_));
			};
		timer_ = this->create_wall_timer(500ms, topictimer_callback);
	}

private:
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<builtin_interfaces::msg::Time>::SharedPtr publisher_;
};
int main(int argc, char ** argv)
{
  (void) argc;
  (void) argv;
  rclcpp::init(argc, argv);
  auto pub_node_ = std::make_shared<PubNode>("topic_pub");

  rclcpp::executors::SingleThreadedExecutor executor_;
  executor_.add_node(pub_node_);
  executor_.spin();

  rclcpp::shutdown();
  printf("hello world shm_test package\n");
  return 0;
}
