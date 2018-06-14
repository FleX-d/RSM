cmake_minimum_required(VERSION 3.0)
project(mcManager VERSION "0.0.1")
set(PROJECT_DESCRIPTION "mosquitto communication manager")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

include(GNUInstallDirs)

SET(privateHeaders
    inc/MCClient.h
    inc/MCClientID.h
    inc/MCManager.h
    inc/MCMessage.h
    inc/MCNewClientRequest.h
    inc/MCTypes.h
    inc/IPCClient.h
    inc/MCOperationRequest.h
    inc/MCRequestAck.h
    inc/IPCInterface.h
)
SET(privateSources
    src/main.cpp
    src/MCClient.cpp
    src/MCClientID.cpp
    src/MCManager.cpp
    src/MCMessage.cpp
    src/MCNewClientRequest.cpp
    src/IPCClient.cpp
    src/MCOperationRequest.cpp
    src/MCRequestAck.cpp
    src/IPCInterface.cpp
)


message(STATUS "mosquittoClientPublicInc: " ${mosquittoClientPublicInc})
message(STATUS "mosquittoClientLib: " ${mosquittoClientLib})

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

add_executable(${PROJECT_NAME} ${privateSources} ${privateHeaders} )
target_link_libraries(${PROJECT_NAME}
    ${mosquittoClientLib}
    ${JSON_PARSER_LIBRARIES}
    ${FLEXD_LOGGER_LIBRARIES}
    ${FLEXD_IPC_CONNECTOR_LIBRARIES}
    ${FLEXD_IPC_EPOLL_LIBRARIES}
    ${FLEXD_IPC_COMMON_LIBRARIES}
    pthread
)

include_directories(inc/ ${mosquittoClientPublicInc} ${JSON_PARSER_INCLUDE_DIRS} ${FLEXD_IPC_CONNECTOR_INCLUDE_DIRS} ${FLEXD_IPC_EPOLL_INCLUDE_DIRS} ${FLEXD_IPC_COMMON_INCLUDE_DIRS} ${FLEXD_LOGGER_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14 -Wall -Wfloat-conversion  ${JSON_PARSER_CFLAGS_OTHER})

add_dependencies(${PROJECT_NAME} mosquittoClient)