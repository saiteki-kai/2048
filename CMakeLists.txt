cmake_minimum_required(VERSION 3.29)
project(C_2048 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(2048 main.cpp)
target_link_libraries(2048 Game App)
