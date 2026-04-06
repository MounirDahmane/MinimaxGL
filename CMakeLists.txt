cmake_minimum_required(VERSION 3.16)
project(TicTacToe VERSION 1.0.0 LANGUAGES C CXX)

# --- Project Settings ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(OpenGL_GL_PREFERENCE GLVND)

# --- Find Dependencies (System-installed) ---
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# --- Path Variables ---
set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/dependencies/imgui")

# --- Source Files ---
set(SOURCES
    # Your Project Source
    src/main.cpp
    src/Application.cpp
    src/Gui.cpp
    src/texture.cpp
    src/vertices.cpp
    src/stb_impl.cpp
    src/Shader.cpp
    src/setup.cpp
    src/Game.cpp

    # GLAD
    dependencies/glad/src/glad.c

    # ImGui Core
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    
    # ImGui Backends
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# --- Create Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- Include Directories ---
target_include_directories(${PROJECT_NAME} PRIVATE
    include                     # Your .h files
    dependencies/glad/include   # GLAD headers
    dependencies/stb-master     # STB headers
    ${IMGUI_DIR}                # imgui.h
    ${IMGUI_DIR}/backends       # imgui_impl_glfw.h, etc.
)

# --- Link Libraries ---
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    ${CMAKE_DL_LIBS}            # Required for GLAD on Linux
)

# --- Resource Management ---
# Syncs your shaders/textures to the build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMENT "Syncing resources to build directory..."
)

# --- Compiler Options ---
if(NOT MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()