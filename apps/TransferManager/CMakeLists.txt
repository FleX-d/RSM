cmake_minimum_required(VERSION 3.0)
project(TransferManager VERSION "0.0.1")
set(PROJECT_DESCRIPTION "Transfer Manager")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

include(GNUInstallDirs)

SET(publicHeaders
    inc/public/FTPDownloadClient.h
    inc/public/FTPTransferClient.h
    inc/public/FTPUploadClient.h
    inc/public/HTTPDownloadClient.h
    inc/public/HTTPTransferClient.h
    inc/public/HTTPUploadClient.h
    inc/public/iTransferClient.h
    inc/public/iTransferRequest.h
    inc/public/TransferManager.h
    inc/public/TMFactory.h
    inc/public/TMConfig.h
    inc/public/StateMachine.h
    inc/public/TransferTypes.h
)
SET(privateHeaders
    inc/TMUtility.h
)
SET(privateSources
    src/FTPDownloadClient.cpp
    src/FTPTransferClient.cpp
    src/FTPUploadClient.cpp
    src/HTTPDownloadClient.cpp
    src/HTTPTransferClient.cpp
    src/HTTPUploadClient.cpp
    src/iTransferClient.cpp
    src/iTransferRequest.cpp
    src/TransferManager.cpp
    src/TMFactory.cpp
    src/TMConfig.cpp
    src/StateMachine.cpp
    src/TMUtility.cpp
    src/main.cpp
)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(fleXdEpoll REQUIRED fleXdEpoll)
if (fleXdEpoll_FOUND)
    message(STATUS "fleXdEpoll libs was found: " ${fleXdEpoll_LIBRARIES})
    message(STATUS "fleXdEpoll inc was found: " ${fleXdEpoll_INCLUDE_DIRS})
endif (fleXdEpoll_FOUND)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_LOGGER REQUIRED fleXdLoggerClient)
if (FLEXD_LOGGER_FOUND)
    message(STATUS "FLEXD_LOGGER libs was found: " ${FLEXD_LOGGER_LIBRARIES})
    message(STATUS "FLEXD_LOGGER inc was found: " ${FLEXD_LOGGER_INCLUDE_DIRS})
endif (FLEXD_LOGGER_FOUND)

add_executable(${PROJECT_NAME} ${privateSources} ${privateHeaders} ${publicHeaders})
target_link_libraries( ${PROJECT_NAME}
    ${FLEXD_LOGGER_LIBRARIES}
    ${fleXdEpoll_LIBRARIES}
    pthread
    curl
)
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14 -Wall -Wfloat-conversion)
target_include_directories(${PROJECT_NAME} PUBLIC inc/public ${fleXdEpoll_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE inc/ ${FLEXD_LOGGER_INCLUDE_DIRS})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

if(${ENABLE_TESTS})
    add_subdirectory(tests)
endif(${ENABLE_TESTS})

if(${ENABLE_EXAMPLES})
    add_subdirectory(examples)
endif(${ENABLE_EXAMPLES})
