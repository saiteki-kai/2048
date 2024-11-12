cmake_minimum_required(VERSION 3.5.0)
project(2048 VERSION 0.1.0 LANGUAGES C CXX)


set(SOURCES
    src/Core.cpp
    src/main.cpp
)

add_executable(2048 ${SOURCES})
target_include_directories(2048 PRIVATE src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(
    2048_test
    tests/Core.cc
    src/Core.cpp
)
target_link_libraries(
    2048_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(2048_test)
