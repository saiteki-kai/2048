# Libraries

add_library(Game grid.cc grid.h game.cc game.h)
add_library(App app.cc app.h style.h game_renderer.cc game_renderer.h utils.cc utils.h)
target_link_libraries(App Game)

# External libraries

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})
target_link_libraries(Game ${SDL3_LIBRARIES})

find_package(SDL3_ttf REQUIRED)
include_directories(${SDL3_ttf_INCLUDE_DIRS})
target_link_libraries(Game SDL3_ttf::SDL3_ttf)

# Resources

set(FONT_FILENAME "ClearSans-Bold.ttf")
set(FONT_SOURCE_PATH "${CMAKE_SOURCE_DIR}/assets/${FONT_FILENAME}")

if (WIN32)
    set(USER_FONT_DIR "$ENV{APPDATA}/C_2048/fonts")
elseif (UNIX)
    set(USER_FONT_DIR "$ENV{HOME}/.local/share/C_2048/fonts")
elseif (APPLE)
    set(USER_FONT_DIR "$ENV{HOME}/Library/Application Support/C_2048/fonts")
endif ()

add_definitions(-DUSER_FONT_PATH="${USER_FONT_DIR}/${FONT_FILENAME}")

file(MAKE_DIRECTORY ${USER_FONT_DIR})
file(COPY ${FONT_SOURCE_PATH} DESTINATION ${USER_FONT_DIR})

message(STATUS "Font copied to: ${USER_FONT_DIR}")
