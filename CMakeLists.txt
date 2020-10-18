cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "mini_raycaster")
project(${PROJECT_NAME} C)

include_directories(lib/include)
include_directories(lib/include/ft_stdio)
include_directories(include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
file(GLOB_RECURSE SOURCES src/**.c)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} lib)
