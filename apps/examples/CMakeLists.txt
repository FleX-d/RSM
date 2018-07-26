

cmake_minimum_required(VERSION 3.0)
project(mcManagerExample VERSION "0.0.1")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

message(STATUS "mosquittoClientPublicInc: " ${mosquittoClientPublicInc})
message(STATUS "mosquittoClientLib: " ${mosquittoClientLib})

message(STATUS "mcManager_SOURCE_DIR: " ${mcManager_SOURCE_DIR})

SET(privateHeaders
    ${mcManager_SOURCE_DIR}/inc/MCClient.h
    ${mcManager_SOURCE_DIR}/inc/MCClientID.h
    ${mcManager_SOURCE_DIR}/inc/MCManager.h
    ${mcManager_SOURCE_DIR}/inc/MCMessage.h
    ${mcManager_SOURCE_DIR}/inc/MCNewClientRequest.h
    ${mcManager_SOURCE_DIR}/inc/MCTypes.h
    ${mcManager_SOURCE_DIR}/inc/IPCClient.h
    ${mcManager_SOURCE_DIR}/inc/MCOperationRequest.h
    ${mcManager_SOURCE_DIR}/inc/MCRequestAck.h
    ${mcManager_SOURCE_DIR}/inc/IPCInterface.h
    ${mcManager_SOURCE_DIR}/inc/GenericClient.h
    GenericClient.h
    IPCInterface.h
)
SET(privateSources
    ${mcManager_SOURCE_DIR}/src/MCClient.cpp
    ${mcManager_SOURCE_DIR}/src/MCClientID.cpp
    ${mcManager_SOURCE_DIR}/src/MCManager.cpp
    ${mcManager_SOURCE_DIR}/src/MCMessage.cpp
    ${mcManager_SOURCE_DIR}/src/MCNewClientRequest.cpp
    ${mcManager_SOURCE_DIR}/src/IPCClient.cpp
    ${mcManager_SOURCE_DIR}/src/MCOperationRequest.cpp
    ${mcManager_SOURCE_DIR}/src/MCRequestAck.cpp
    ${mcManager_SOURCE_DIR}/src/IPCInterface.cpp
    ${mcManager_SOURCE_DIR}/src/GenericClient.cpp
)


include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(JSON_PARSER REQUIRED jsonParser)
if (JSON_PARSER_FOUND)
    message(STATUS "JSON_PARSER libs was found: " ${JSON_PARSER_LIBRARIES})
    message(STATUS "JSON_PARSER inc was found: " ${JSON_PARSER_INCLUDE_DIRS})
endif (JSON_PARSER_FOUND)


include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_IPC_CONNECTOR REQUIRED fleXdIPCConnector)
if (FLEXD_IPC_CONNECTOR_FOUND)
    message(STATUS "FLEXD_IPC_CONNECTOR libs was found: " ${FLEXD_IPC_CONNECTOR_LIBRARIES})
    message(STATUS "FLEXD_IPC_CONNECTOR inc was found: " ${FLEXD_IPC_CONNECTOR_INCLUDE_DIRS})
endif (FLEXD_IPC_CONNECTOR_FOUND)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_IPC_EPOLL REQUIRED fleXdEpoll)
if (FLEXD_IPC_EPOLL_FOUND)
    message(STATUS "FLEXD_IPC_EPOLL libs was found: " ${FLEXD_IPC_EPOLL_LIBRARIES})
    message(STATUS "FLEXD_IPC_EPOLL inc was found: " ${FLEXD_IPC_EPOLL_INCLUDE_DIRS})
endif (FLEXD_IPC_EPOLL_FOUND)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_IPC_COMMON REQUIRED fleXdIPCCommon)
if (FLEXD_IPC_COMMON_FOUND)
    message(STATUS "FLEXD_IPC_COMMON libs was found: " ${FLEXD_IPC_COMMON_LIBRARIES})
    message(STATUS "FLEXD_IPC_COMMON inc was found: " ${FLEXD_IPC_COMMON_INCLUDE_DIRS})
endif (FLEXD_IPC_COMMON_FOUND)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_LOGGER REQUIRED fleXdLoggerClient)
if (FLEXD_LOGGER_FOUND)
    message(STATUS "FLEXD_LOGGER libs was found: " ${FLEXD_LOGGER_LIBRARIES})
    message(STATUS "FLEXD_LOGGER inc was found: " ${FLEXD_LOGGER_INCLUDE_DIRS})
endif (FLEXD_LOGGER_FOUND)

include_directories(
${mosquittoClientPublicInc}
${mcManager_SOURCE_DIR}/inc
${JSON_PARSER_INCLUDE_DIRS} 
${FLEXD_IPC_CONNECTOR_INCLUDE_DIRS} 
${FLEXD_IPC_EPOLL_INCLUDE_DIRS} 
${FLEXD_IPC_COMMON_INCLUDE_DIRS} 
${FLEXD_LOGGER_INCLUDE_DIRS}
)

set (CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wfloat-conversion")
add_executable(${PROJECT_NAME}Manager Manager.cpp ${privateHeaders} ${privateSources})
target_compile_options(${PROJECT_NAME}Manager PUBLIC -std=c++14 -Wall -Wfloat-conversion)
target_link_libraries(${PROJECT_NAME}Manager
    ${mosquittoClientLib}
    ${JSON_PARSER_LIBRARIES}
    ${FLEXD_LOGGER_LIBRARIES}
    ${FLEXD_IPC_CONNECTOR_LIBRARIES}
    ${FLEXD_IPC_EPOLL_LIBRARIES}
    ${FLEXD_IPC_COMMON_LIBRARIES}
    pthread
)
add_dependencies(${PROJECT_NAME}Manager mosquittoClient)

add_executable(${PROJECT_NAME}Sender Sender.cpp ${privateHeaders})
target_compile_options(${PROJECT_NAME}Sender PUBLIC -std=c++14 -Wall -Wfloat-conversion)
target_link_libraries(${PROJECT_NAME}Sender
    ${mosquittoClientLib}
    ${JSON_PARSER_LIBRARIES}
    ${FLEXD_LOGGER_LIBRARIES}
    ${FLEXD_IPC_CONNECTOR_LIBRARIES}
    ${FLEXD_IPC_EPOLL_LIBRARIES}
    ${FLEXD_IPC_COMMON_LIBRARIES}
    pthread
)
add_dependencies(${PROJECT_NAME}Sender mosquittoClient)

add_executable(${PROJECT_NAME}Monitor Monitor.cpp ${privateHeaders} )
target_compile_options(${PROJECT_NAME}Monitor PUBLIC -std=c++14 -Wall -Wfloat-conversion)
target_link_libraries(${PROJECT_NAME}Monitor
    ${mosquittoClientLib}
    ${JSON_PARSER_LIBRARIES}
    ${FLEXD_LOGGER_LIBRARIES}
    ${FLEXD_IPC_CONNECTOR_LIBRARIES}
    ${FLEXD_IPC_EPOLL_LIBRARIES}
    ${FLEXD_IPC_COMMON_LIBRARIES}
    pthread
)
add_dependencies(${PROJECT_NAME}Monitor mosquittoClient)
