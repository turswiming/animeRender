cmake_minimum_required(VERSION 3.25)

project(AnimeRenderer VERSION 2.1)
configure_file(TutorialConfig.h.in TutorialConfig.h)

set(CMAKE_CXX_STANDARD 11)

# Add GLFW and glad as subdirectories
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# List all source files explicitly
set(SOURCES
        main.cpp
        main2.cpp
        main3_shader.cpp
        # Add more source files as necessary
        )

# Create an executable for each source file
foreach(SOURCE ${SOURCES})
    # Extract the file name without the extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    # Create an executable with the same name as the source file
    add_executable(${EXECUTABLE_NAME} ${SOURCE} module/shader/Shader.cpp module/shader/Shader.h)
    # Link against GLFW and glad
    target_link_libraries(${EXECUTABLE_NAME} glfw glad)
    # Add include files
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_BINARY_DIR})
endforeach()