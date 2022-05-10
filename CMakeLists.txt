cmake_minimum_required(VERSION 3.14)
project(3d_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE_FILES main.cpp)

add_definitions(-DSFML_STATIC)
include_directories("inc/")
add_executable(3d_engine main.cpp inc/scene.hpp src/scene.cpp inc/camera.hpp src/camera.cpp inc/matrix.hpp)
include_directories(/usr/local/include)


include_directories(${SFML_INCLUDE_DIRS})
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(3d_engine sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
