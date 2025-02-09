cmake_minimum_required(VERSION 3.10)
project(OpenGL_Project)

# # Use C++17 standard
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
# Enable compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find pkg-config
find_package(PkgConfig REQUIRED)

# Find GLFW using pkg-config
pkg_check_modules(GLFW REQUIRED glfw3)

# Include GLFW directories

set(INCLUDE_DIRS 
  ${GLFW_INCLUDE_DIRS}
  include
)

include_directories(${INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})

include_directories(include)

# Set sources
set(SOURCES
    src/main.c
    src/glad.c
)

# Add the executable
add_executable(app ${SOURCES})

# Link GLFW, GLAD, and system libraries
target_link_libraries(app ${GLFW_LIBRARIES} -ldl)
