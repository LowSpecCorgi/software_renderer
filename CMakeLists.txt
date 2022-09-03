cmake_minimum_required(VERSION 3.7...3.21)

# CMake versions < 3.12 do not support .., so policy is manually set here if needed
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Configure build directory
if(NOT "${ROOT}/build")
  file(MAKE_DIRECTORY "${ROOT}/build")
endif()

# C configuration
set(CMAKE_C_STANDARD 11)

# Variables
set(PROJ_NAME "software_renderer" CACHE STRING "")
set(PROJ_VERSION 0.0.1 CACHE STRING "")
set(PROJ_DESCRIPTION "Minimal C software renderer" CACHE STRING "")
set(CMAKE_CXX_COMPILER_FORCED True)

project(${PROJ_NAME} VERSION ${PROJ_VERSION} DESCRIPTION ${PROJ_DESCRIPTION} LANGUAGES C)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.c src/*.h)

add_executable(${PROJ_NAME} ${SRC_FILES})