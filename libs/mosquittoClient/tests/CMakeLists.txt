cmake_minimum_required(VERSION 3.0)
project(MosquittoTests VERSION "0.0.1")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

message(STATUS "mosquittoClientPublicInc: " ${mosquittoClientPublicInc})
message(STATUS "mosquittoClientLib: " ${mosquittoClientLib})


add_executable(example example.cpp)
target_include_directories(example PRIVATE ${mosquittoClientPublicInc})
target_compile_options(example PUBLIC -std=c++14 -Wall -Wfloat-conversion)
target_link_libraries(example
    ${mosquittoClientLib}
)
add_dependencies(example mosquittoClient)
