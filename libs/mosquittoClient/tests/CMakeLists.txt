cmake_minimum_required(VERSION 3.0)
project(jsonParserTests VERSION "0.0.1")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

message(STATUS "mosquittoClientPublicInc: " ${mosquittoClientPublicInc})
message(STATUS "mosquittoClientLib: " ${mosquittoClientLib})

include_directories(${mosquittoClientPublicInc})
add_executable(example example.cpp)
target_link_libraries(example
    ${mosquittoClientLib}
    pthread
)
add_dependencies(example mosquittoClient)

