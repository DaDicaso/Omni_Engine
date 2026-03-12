cmake_minimum_required(VERSION 3.16)
project(GamePhysicsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC 
    external/glad/include
)

include_directories(external/glfw/include)

add_executable(physics_engine
    src/main.cpp
)

target_include_directories(physics_engine
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

add_executable(particle_sandbox
    demos/particle_sandbox/particle_sandbox.cpp
    src/physics/particle.cpp
)

target_include_directories(particle_sandbox PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    external/glad/include
    external/glfw/include
)

target_link_libraries(particle_sandbox
    glfw
    glad
    GL
)