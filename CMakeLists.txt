cmake_minimum_required(VERSION 3.14)
project(lab-2-13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(SOURCE_FILES main.cpp)

add_definitions(-DSFML_STATIC)
include_directories("inc/")
add_executable(lab-2-13 main.cpp inc/scene.hpp src/scene.cpp inc/camera.hpp src/camera.cpp inc/matrix.hpp)
include_directories(/usr/local/include)


include_directories(${SFML_INCLUDE_DIRS})
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(lab-2-13 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
