cmake_minimum_required(VERSION 3.10)

project(nodes_and_dots)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set vcpkg toolchain file path
set(CMAKE_TOOLCHAIN_FILE "C:/Tools/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Find the required packages
find_package(SFML 2.5 COMPONENTS system window graphics CONFIG REQUIRED)

# Recursively get all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

# Add executable
add_executable(nodes_and_dots ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(nodes_and_dots PRIVATE 
    include 
    src
    src/rendering
    src/utils
    src/objects
)

# Link SFML libraries
target_link_libraries(nodes_and_dots 
    PRIVATE 
    sfml-system 
    sfml-window 
    sfml-graphics
)