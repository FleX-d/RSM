cmake_minimum_required(VERSION 3.0)
add_subdirectory(lib)

if(${ENABLE_TESTS})
    add_subdirectory(tests)
endif(${ENABLE_TESTS})

SET(mosquittoClientPublicInc "${mosquittoClientPublicInc}" PARENT_SCOPE)
SET(mosquittoClientLib "${mosquittoClientLib}" PARENT_SCOPE)
