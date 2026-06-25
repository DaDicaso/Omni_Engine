cmake_minimum_required(VERSION 3.16)

project(OmniEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------
# GLFW
# ------------------------------------------------------------

add_subdirectory(external/glfw)

# ------------------------------------------------------------
# GLAD
# ------------------------------------------------------------

add_library(glad
    external/glad/src/glad.c
)

target_include_directories(glad
PUBLIC
    external/glad/include
)

# ------------------------------------------------------------
# Source Files
# ------------------------------------------------------------

set(ENGINE_SOURCES

)

set(LAB_SOURCES

    lab/experiment_manager.cpp

    lab/physics_lab.cpp

    lab/experiments/empty/empty_experiment.cpp

)

set(APP_SOURCES

    app/main.cpp

)

# ------------------------------------------------------------
# Executable
# ------------------------------------------------------------

add_executable(OmniPhysicsLab

    ${ENGINE_SOURCES}

    ${LAB_SOURCES}

    ${APP_SOURCES}

)

# ------------------------------------------------------------
# Include Directories
# ------------------------------------------------------------

target_include_directories(OmniPhysicsLab

PUBLIC

    ${CMAKE_SOURCE_DIR}

    external/glad/include

    external/glfw/include

)

# ------------------------------------------------------------
# Link Libraries
# ------------------------------------------------------------

target_link_libraries(OmniPhysicsLab

PRIVATE

    glfw

    glad

    GL

)