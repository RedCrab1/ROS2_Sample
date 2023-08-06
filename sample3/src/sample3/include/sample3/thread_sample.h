
#pragma once
#include <string>

#include "rclcpp/rclcpp.hpp"

class ThreadSample: public rclcpp::Node
{
	public:
		explicit ThreadSample(const std::string& node_name);
		~ThreadSample(){};
	
	private:
		rclcpp::TimerBase::SharedPtr print_timer_;
};
