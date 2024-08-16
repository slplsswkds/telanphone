cmake_minimum_required(VERSION 3.28)
project(telanphone)

add_definitions("-std=c++23")
add_definitions("-O2")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(telanphone
        src/ArgsCLI.cpp
        src/ArgsCLI.h)

# ----- DEPENDENCIES ----------
find_package(CLI11 CONFIG REQUIRED)

target_sources(telanphone PRIVATE src/main.cpp)
target_link_libraries(telanphone PRIVATE CLI11::CLI11)