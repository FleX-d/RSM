cmake_minimum_required(VERSION 3.0)
project(TransferManagerExamples VERSION "0.0.1")
set(PROJECT_DESCRIPTION "Transfer Manager example")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

message(STATUS "TransferManager_SOURCE_DIR: " ${TransferManager_SOURCE_DIR})


include(GNUInstallDirs)

SET(publicHeaders
    ${TransferManager_SOURCE_DIR}/inc/public
)
SET(privateHeaders
    ${TransferManager_SOURCE_DIR}/inc/
)
SET(privateSources
    ${TransferManager_SOURCE_DIR}/src/
)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_IPC_EPOLL REQUIRED fleXdEpoll)
if (FLEXD_IPC_EPOLL_FOUND)
    message(STATUS "FLEXD_IPC_EPOLL libs was found: " ${FLEXD_IPC_EPOLL_LIBRARIES})
    message(STATUS "FLEXD_IPC_EPOLL inc was found: " ${FLEXD_IPC_EPOLL_INCLUDE_DIRS})
endif (FLEXD_IPC_EPOLL_FOUND)

include_directories(
${TransferManager_SOURCE_DIR}/inc
${FLEXD_IPC_EPOLL_INCLUDE_DIRS} 
)
set (CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wfloat-conversion")
add_executable(${PROJECT_NAME} main.cpp ${privateHeaders} ${privateSources})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14 -Wall -Wfloat-conversion)
target_link_libraries(${PROJECT_NAME}
    ${FLEXD_IPC_EPOLL_LIBRARIES}
    pthread
    curl
)

 
