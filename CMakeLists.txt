cmake_minimum_required(VERSION 3.25)
project(LearnOpengl VERSION 2.1)

configure_file(TutorialConfig.h.in TutorialConfig.h)

set(CMAKE_CXX_STANDARD 11)

# Add GLFW and glad as a subdirectory
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# Include GLFW and glad headers
include_directories(${GLFW_INCLUDE_DIRS})


# Create the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Link against GLFW and glad
target_link_libraries(${PROJECT_NAME} glfw glad)

#add include files
target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        )