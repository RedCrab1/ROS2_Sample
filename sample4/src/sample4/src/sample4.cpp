#include <cstdio>
#include <memory>
#include <string>
#include <utility>
#include "rclcpp/rclcpp.hpp"
//#include "builtin_interfaces/msg/time.hpp"
#include <chrono>

class PubNode : public rclcpp::Node
{
	public:
		explicit PubNode(const std::string& node_name): 
			Node(node_name, rclcpp::NodeOptions().use_intra_process_comms(true))
	{
		using namespace std::chrono_literals;
		publisher_ = this->create_publisher<builtin_interfaces::msg::Time>(
				"current_time",
				10
				);
		auto topictimer_callback = 
			[&]()->void {
				builtin_interfaces::msg::Time::UniquePtr timestamp_ = 
					std::make_unique<builtin_interfaces::msg::Time>(this->get_clock()->now());
				RCLCPP_INFO_STREAM(this->get_logger(), "pub:Addr is:" << reinterpret_cast<std::uintptr_t>(timestamp_.get()));
				publisher_->publish(std::move(timestamp_));
			};
		
		timer_ = this->create_wall_timer(std::chrono::milliseconds(500), topictimer_callback);
	}
	
	private:
		rclcpp::TimerBase::SharedPtr timer_;
		rclcpp::Publisher<builtin_interfaces::msg::Time>::SharedPtr publisher_;

};

class SubNode : public rclcpp::Node
{
	public:
		explicit SubNode(const std::string & node_name):
			Node(node_name, rclcpp::NodeOptions().use_intra_process_comms(true))
		{
			subscriber_ = this->create_subscription<builtin_interfaces::msg::Time>(
					"current_time",
					10,
					std::bind(&SubNode::count_sub_callback, this, std::placeholders::_1));
		}

	private:
		rclcpp::Subscription<builtin_interfaces::msg::Time>::SharedPtr subscriber_;
		void count_sub_callback(const builtin_interfaces::msg::Time::UniquePtr msg)
		{
			RCLCPP_INFO_STREAM(this->get_logger(), "sub::Addr is: " << 
					reinterpret_cast<std::uintptr_t>(msg.get()));
		}
};

void another_executor()
{
	rclcpp::executors::SingleThreadedExecutor executor_;
	auto sub_node_ = std::make_shared<SubNode>("topic_sub");
	executor_.add_node(sub_node_);
	executor_.spin();
}

int main(int argc, char ** argv)
{
  
  rclcpp::init(argc, argv);
  auto pub_node_ = std::make_shared<PubNode>("topic_pub");
  rclcpp::executors::SingleThreadedExecutor executor_;
  
  std::thread another(another_executor);

  executor_.add_node(pub_node_);
  executor_.spin();

  another.join();
  rclcpp::shutdown();

  return 0;
}
