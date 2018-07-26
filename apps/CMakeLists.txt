cmake_minimum_required(VERSION 3.0)
add_subdirectory(MCManager)

if(${ENABLE_TESTS})
    add_subdirectory(tests)
    add_subdirectory(examples)
endif(${ENABLE_TESTS})
