cmake_minimum_required(VERSION 3.6)
project(project6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra -pedantic -pedantic-errors")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=native -D_GLIBCXX_DEBUG")

# dear student -- in the end, all .h & .cpp source files should be
#  in the following list of SOURCE_FILES
set(SOURCE_FILES
        main.cpp)

#sdl
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

#sdl mixer
find_library(SDL_MIXER_LIBRARY
        NAMES SDL2_mixer
        HINTS
        ENV SDLMIXERDIR
        ENV SDLDIR
        PATH_SUFFIXES lib
        )
include_directories(${SDL2_INCLUDE_DIRS})


add_executable(project6 ${SOURCE_FILES})

target_link_libraries(project6 SDL2 SDL2_mixer stdc++fs)