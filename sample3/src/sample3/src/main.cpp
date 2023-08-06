#include "sample3/thread_sample.h"
#include <memory>
#include <vector>

#include <string>
#include "rclcpp/rclcpp.hpp"

int main(int argc, char ** argv)
{
	rclcpp::init(argc, argv);
	uint32_t node_count(0);
	bool is_multi(false);
	std::vector<std::shared_ptr<ThreadSample>> node_vector;

	rclcpp::executors::SingleThreadedExecutor executor_s;
	rclcpp::executors::MultiThreadedExecutor executor_m;

	if(argc >= 3)
	{
		int input_count = atoi(argv[1]);
		node_count = input_count > 0 ? input_count : 0;

		node_vector.reserve(node_count);
		std::string multi_flag = static_cast<std::string>(argv[2]);

		if(multi_flag == std::string("m")){
			is_multi = true;
		}
		else if (multi_flag == std::string("s")){
			is_multi = false;
		}
		else{
			std::cout<<"Example ros2 run sample3 sample3 <node_count> s/m" << std::endl;
			return 0;
		}
	}
	else
	{
		        std::cout<<"Example ros2 run sample3 sample3 <node_count> s/m" << std::endl;
                        return 0;
	}

	for (int i = node_count; i > 0; i--){
		node_vector.push_back(
			std::make_shared<ThreadSample>("cpp_node_a_" + std::to_string(i)));

		if(is_multi)
		{
			executor_m.add_node(node_vector.back()->get_node_base_interface());
		}
		else
		{
			executor_s.add_node(node_vector.back()->get_node_base_interface());
		}
	}

	if(is_multi)
	{
		executor_m.spin();
	}
	else
	{
		executor_s.spin();
	}

	rclcpp::shutdown();
	return 0;
}
