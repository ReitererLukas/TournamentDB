cmake_minimum_required(VERSION 3.10)
project(TournamentDB)

set(CMAKE_CXX_STANDARD 17)

# Add debug flags for Debug builds
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Add common warning flags
add_compile_options(-Wall -Wextra -Wpedantic)

# Add include directories for all headers
include_directories(src/include)
include_directories(src/include/commands)
include_directories(src/include/util)
include_directories(src/include/db)
include_directories(src/include/commandmodels)
include_directories(src/include/models)
include_directories(src/include/shared)

# Gather all source files
file(GLOB SOURCES
    "main.cpp"
    "src/source/commands/*.cpp"
    "src/source/util/*.cpp"
    "src/source/db/*.cpp"
    "src/source/commandmodels/*.cpp"
    "src/source/models/*.cpp"
    "src/source/shared/*.cpp"
)

add_executable(TournamentDB ${SOURCES})