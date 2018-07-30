cmake_minimum_required(VERSION 3.0)
project(TransferManagerTests VERSION "0.0.1")

message(STATUS "***" )
message(STATUS "* " ${PROJECT_NAME})
message(STATUS "***")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTEST REQUIRED gtest>=1.7.0)
pkg_check_modules(GMOCK REQUIRED gmock>=1.7.0)

message(STATUS "GTEST_LIBRARIES: " ${GTEST_LIBRARIES})
message(STATUS "GTEST_LIBRARIES: " ${GMOCK_LIBRARIES})
message(STATUS "GTEST_LIBRARIES: " ${GTEST_INCLUDE_DIRS})
message(STATUS "GTEST_LIBRARIES: " ${GMOCK_INCLUDE_DIRS})


message(STATUS "TransferManager_SOURCE_DIR: " ${TransferManager_SOURCE_DIR})

SET(publicHeaders
    ${TransferManager_SOURCE_DIR}/inc/public/FTPDownloadClient.h
    ${TransferManager_SOURCE_DIR}/inc/public/FTPTransferClient.h
    ${TransferManager_SOURCE_DIR}/inc/public/FTPUploadClient.h
    ${TransferManager_SOURCE_DIR}/inc/public/HTTPDownloadClient.h
    ${TransferManager_SOURCE_DIR}/inc/public/HTTPTransferClient.h
    ${TransferManager_SOURCE_DIR}/inc/public/HTTPUploadClient.h
    ${TransferManager_SOURCE_DIR}/inc/public/iTransferClient.h
    ${TransferManager_SOURCE_DIR}/inc/public/iTransferRequest.h
    ${TransferManager_SOURCE_DIR}/inc/public/TransferManager.h
    ${TransferManager_SOURCE_DIR}/inc/public/TMFactory.h
    ${TransferManager_SOURCE_DIR}/inc/public/TMConfig.h
    ${TransferManager_SOURCE_DIR}/inc/public/StateMachine.h
    ${TransferManager_SOURCE_DIR}/inc/public/TransferTypes.h
)
SET(privateHeaders
    ${TransferManager_SOURCE_DIR}/inc/TMUtility.h
)
SET(privateSources
    ${TransferManager_SOURCE_DIR}/src/FTPDownloadClient.cpp
    ${TransferManager_SOURCE_DIR}/src/FTPTransferClient.cpp
    ${TransferManager_SOURCE_DIR}/src/FTPUploadClient.cpp
    ${TransferManager_SOURCE_DIR}/src/HTTPDownloadClient.cpp
    ${TransferManager_SOURCE_DIR}/src/HTTPTransferClient.cpp
    ${TransferManager_SOURCE_DIR}/src/HTTPUploadClient.cpp
    ${TransferManager_SOURCE_DIR}/src/iTransferClient.cpp
    ${TransferManager_SOURCE_DIR}/src/iTransferRequest.cpp
    ${TransferManager_SOURCE_DIR}/src/TransferManager.cpp
    ${TransferManager_SOURCE_DIR}/src/TMFactory.cpp
    ${TransferManager_SOURCE_DIR}/src/TMConfig.cpp
    ${TransferManager_SOURCE_DIR}/src/StateMachine.cpp
    ${TransferManager_SOURCE_DIR}/src/TMUtility.cpp
    iTransferRequestTest.cpp
    FactoryTest.cpp
    main.cpp
)


include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_IPC_EPOLL REQUIRED fleXdEpoll)
if (FLEXD_IPC_EPOLL_FOUND)
    message(STATUS "FLEXD_IPC_EPOLL libs was found: " ${FLEXD_IPC_EPOLL_LIBRARIES})
    message(STATUS "FLEXD_IPC_EPOLL inc was found: " ${FLEXD_IPC_EPOLL_INCLUDE_DIRS})
endif (FLEXD_IPC_EPOLL_FOUND)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_LOGGER REQUIRED fleXdLoggerClient)
if (FLEXD_LOGGER_FOUND)
    message(STATUS "FLEXD_LOGGER libs was found: " ${FLEXD_LOGGER_LIBRARIES})
    message(STATUS "FLEXD_LOGGER inc was found: " ${FLEXD_LOGGER_INCLUDE_DIRS})
endif (FLEXD_LOGGER_FOUND)

include(FindPkgConfig)
find_package(PkgConfig REQUIRED)
pkg_search_module(FLEXD_IPC_COMMON REQUIRED fleXdIPCCommon)
if (FLEXD_IPC_COMMON_FOUND)
    message(STATUS "FLEXD_IPC_COMMON libs was found: " ${FLEXD_IPC_COMMON_LIBRARIES})
    message(STATUS "FLEXD_IPC_COMMON inc was found: " ${FLEXD_IPC_COMMON_INCLUDE_DIRS})
endif (FLEXD_IPC_COMMON_FOUND)

include_directories(
${TransferManager_SOURCE_DIR}/inc/public
${TransferManager_SOURCE_DIR}/inc
${FLEXD_IPC_EPOLL_INCLUDE_DIRS} 
${GTEST_INCLUDE_DIRS}
${GMOCK_INCLUDE_DIRS}
${FLEXD_LOGGER_INCLUDE_DIRS}
${FLEXD_IPC_COMMON_INCLUDE_DIRS}
)

set (CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wfloat-conversion")
add_executable(${PROJECT_NAME} main.cpp ${privateHeaders} ${privateSources})
target_compile_options(${PROJECT_NAME} PUBLIC -std=c++14 -Wall -Wfloat-conversion)
target_link_libraries(${PROJECT_NAME}
    ${FLEXD_IPC_EPOLL_LIBRARIES}
     ${FLEXD_IPC_COMMON_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${GMOCK_LIBRARIES}
    ${FLEXD_LOGGER_LIBRARIES}
    pthread
    curl
)

