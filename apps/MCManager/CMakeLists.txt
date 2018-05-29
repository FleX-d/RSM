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

add_executable(${PROJECT_NAME} ${privateSources} ${privateHeaders} )
target_link_libraries(${PROJECT_NAME}
    ${mosquittoClientLib}
    ${JSON_PARSER_LIBRARIES}
    pthread
)

include_directories(inc/ ${mosquittoClientPublicInc} ${JSON_PARSER_INCLUDE_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14 -Wall -Wfloat-conversion  ${JSON_PARSER_CFLAGS_OTHER})

add_dependencies(${PROJECT_NAME} mosquittoClient)