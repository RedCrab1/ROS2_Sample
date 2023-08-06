#include "sample3/thread_sample.h"

#include <chrono>
#include <string>
#include <thread>
#include <unistd.h>
#include "sys/types.h"
#include "rclcpp/rclcpp.hpp"

ThreadSample::ThreadSample(const std::string& node_name): rclcpp::Node(node_name)
{
	auto printtimer_callback = 
	[&]()->void {
		pid_t pid = getpid();
		std::cout<< this->get_name() << ": pid is " << pid << ", thread id is " << std::this_thread::get_id() << std::endl;
	};

	print_timer_ = this->create_wall_timer(std::chrono::milliseconds(500), printtimer_callback);
}
