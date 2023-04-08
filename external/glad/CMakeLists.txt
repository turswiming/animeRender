cmake_minimum_required(VERSION 3.25)

project(glad)

# Specify include directories
include_directories(include)

# Create GLAD library
add_library(glad STATIC src/glad.c)

# Specify include directories for targets that consume this library
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
