cmake_minimum_required(VERSION 3.5)
project(common)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

message("222 ${CMAKE_CURRENT_SOURCE_DIR}")
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

#add_executable(common src/common.cpp)
add_library(common SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/common.cpp)

message("1111 ${CMAKE_CURRENT_SOURCE_DIR}")
#target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#add_library(common src/common.cpp)

target_include_directories(common PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  common
  "rclcpp"
)

ament_export_include_directories(include)

#ament_export_targets(common)

install(DIRECTORY include/
  DESTINATION include
)

install(
	TARGETS common
	LIBRARY DESTINATION lib
	)
#install(TARGETS common
#  DESTINATION lib/${PROJECT_NAME})

ament_export_libraries(${PROJECT_NAME})

#ament_export_targets(common)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
