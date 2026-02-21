cmake_minimum_required(VERSION 3.16)
project(GamePhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(physics_engine
    src/main.cpp
)

target_include_directories(physics_engine
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

