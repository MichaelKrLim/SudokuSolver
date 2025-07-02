cmake_minimum_required(VERSION 3.20)
project(SudokuSolver LANGUAGES CXX)
include(cmake/CPM.cmake)
CPMAddPackage(
    NAME ImGui
    GITHUB_REPOSITORY ocornut/imgui
    GIT_TAG v1.92.0
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wpedantic
    -O3
)