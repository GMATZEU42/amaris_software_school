cmake_minimum_required( VERSION 3.15 )

project(amaris_school)

# Build runtime in the same directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(amaris)
add_subdirectory(school)

add_subdirectory(gtest)