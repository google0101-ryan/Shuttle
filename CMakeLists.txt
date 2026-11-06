cmake_minimum_required(VERSION 3.10)

project(shuttle)

add_subdirectory(SDL_FontCache)

set(SOURCES src/ui/MEDWindow.cpp
            src/ui/Keyboard.cpp
            src/ui/Button.cpp
            src/ui/CenterConsole.cpp
            src/ui/Switch.cpp
            src/dps/DPS.cpp
            src/dps/GPC.cpp
            src/dps/IDP.cpp
            src/dps/MemoryConfig.cpp
            src/dps/Time.cpp
            src/dps/SW/SWUtil.cpp
            src/dps/SW/GpcMemory.cpp
            src/dps/SW/BfsMemory.cpp
            src/dps/SW/GNC/MM101.cpp
            src/dps/SW/GNC/BFS_MM101.cpp
            src/main.cpp)

set(INCLUDES
                src/ui/MEDWindow.h
                src/ui/Keyboard.h
                src/ui/Button.h
                src/ui/CenterConsole.h
                src/ui/Switch.h
                src/dps/DPS.h
                src/dps/GPC.h
                src/dps/IDP.h
                src/dps/MemoryConfig.h
                src/dps/Time.h
                src/dps/SW/GpcMemory.h
                src/dps/SW/BfsMemory.h
                src/dps/SW/GNC/MM101.h
                src/dps/SW/GNC/BFS_MM101.h
                src/dps/SW/Page.h
                src/dps/SW/SWUtil.h
                src/util/Parser.h)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

add_executable(shuttle ${SOURCES} ${INCLUDES})
include_directories(
    ${CMAKE_SOURCE_DIR}/src/dps
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
target_link_libraries(shuttle PRIVATE SDL2::SDL2 SDL2_ttf::SDL2_ttf FontCache SDL2_image::SDL2_image)

file(GLOB RESOURCES
    res/*)

file(COPY ${RESOURCES} DESTINATION ${CMAKE_BINARY_DIR}/res)