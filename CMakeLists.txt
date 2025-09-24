cmake_minimum_required(VERSION 3.2)
project(SmartClock)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
else()
  set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
endif()

include_directories(json/includes)
add_subdirectory(src)
set(CMAKE_BUILD_TYPE Debug)	