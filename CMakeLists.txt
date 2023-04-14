cmake_minimum_required(VERSION 3.25)

project(AnimeRenderer VERSION 2.1)
configure_file(TutorialConfig.h.in TutorialConfig.h)

set(CMAKE_CXX_STANDARD 11)

# Add GLFW and glad as subdirectories
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)

# Include the glm headers
target_include_directories(main3_shader PUBLIC external/glm)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE external/stb)
target_sources(stb_image INTERFACE external/stb/stb_image.h)

# List all source files explicitly
set(SOURCES
        main.cpp
        main2.cpp
        main3_shader.cpp
        main4_texture.cpp
        # Add more source files as necessary
        )
file(
        COPY
        Shaders
        Images
        DESTINATION  ${PROJECT_BINARY_DIR})
# Create an executable for each source file
foreach(SOURCE ${SOURCES})
    # Extract the file name without the extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
    include_directories(external/stb)
    # Create an executable with the same name as the source file
    add_executable(${EXECUTABLE_NAME} ${SOURCE} module/shader/Shader.cpp module/texture/texture.cpp)
    # Link against GLFW and glad
    target_link_libraries(${EXECUTABLE_NAME} glfw glad glm)
    # Add include files
    target_include_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_BINARY_DIR})
endforeach()