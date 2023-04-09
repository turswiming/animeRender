cmake_minimum_required(VERSION 3.25)
project(AnimeRenderer VERSION 2.1)
set(CMAKE_CXX_STANDARD 11)


# Add GLFW and glad as a subdirectory
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# Create the main executable
#add_executable(${PROJECT_NAME} main.cpp)

# Link against GLFW and glad
#target_link_libraries(${PROJECT_NAME} glfw glad)
# Find all main*.cpp files and store in list mains
file(GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
foreach(mainfile IN LISTS mains)
    configure_file(TutorialConfig.h.in TutorialConfig.h)


    # Include GLFW headers
    include_directories(${GLFW_INCLUDE_DIRS})
    # Get file name without directory
    get_filename_component(main-name ${mainfile} NAME_WE)
    add_executable(${main-name} ${mainfile})
    # Link against GLFW and glad
    target_link_libraries(${main-name} glfw glad)
    #add include files
    target_include_directories(${main-name} PUBLIC
            ${PROJECT_BINARY_DIR}
            )
endforeach()