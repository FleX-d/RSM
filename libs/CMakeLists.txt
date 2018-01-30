cmake_minimum_required(VERSION 3.0)
add_subdirectory(mosquittoClient)

SET(mosquittoClientPublicInc "${mosquittoClientPublicInc}" PARENT_SCOPE)
SET(mosquittoClientLib "${mosquittoClientLib}" PARENT_SCOPE)
