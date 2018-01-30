cmake_minimum_required(VERSION 3.0)
project(mosquittoClient VERSION "0.0.1")
set(PROJECT_DESCRIPTION "mosquitto client")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

include(GNUInstallDirs)

SET(publicHeaders
    inc/public/iMosquittoClient.h
    inc/public/MosquittoConnection.h
    inc/public/MosquittoSetting.h
    inc/public/MqttMessage.h
    inc/public/MqttTypes.h
)
SET(privateHeaders
    inc/FlexLogger.h
    inc/MqttUtils.h
)
SET(privateSources
    src/iMosquittoClient.cpp
    src/MosquittoConnection.cpp
    src/MosquittoSetting.cpp
    src/MqttMessage.cpp
)

add_library(${PROJECT_NAME} SHARED ${privateSources})
set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${publicHeaders}")
configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

find_library(MOSQUITTOPP_LIBRARY NAMES mosquittopp)
if (${MOSQUITTOPP_LIBRARY})
    message(STATUS "mosquittopp was found: " ${MOSQUITTOPP_LIBRARY})
endif (${MOSQUITTOPP_LIBRARY})

target_include_directories(${PROJECT_NAME} PUBLIC inc/public)
target_include_directories(${PROJECT_NAME} PRIVATE inc/)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14 -Wall -Wfloat-conversion)

target_link_libraries(${PROJECT_NAME}
    ${MOSQUITTOPP_LIBRARY}
)

SET(mosquittoClientPublicInc "${mosquittoClient_SOURCE_DIR}/inc/public" PARENT_SCOPE)
SET(mosquittoClientLib "${PROJECT_NAME}" PARENT_SCOPE)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
