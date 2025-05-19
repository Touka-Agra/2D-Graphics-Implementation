cmake_minimum_required(VERSION 3.26)
project(Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project main.cpp)

# Link to GDI32 for Windows graphics
target_link_libraries(Project gdi32 user32)

