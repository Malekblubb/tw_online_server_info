project(tw_online_server_info)
cmake_minimum_required(VERSION 2.8)
file(GLOB_RECURSE SRC_LIST "./src/*.cpp")
include_directories("external/mlk/include" "external/twl/include")
add_executable(${PROJECT_NAME} ${SRC_LIST})
SET(CMAKE_CXX_FLAGS "-std=c++11")

