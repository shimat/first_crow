cmake_minimum_required(VERSION 3.20)
project(first_crow CXX)

include(CheckIncludeFileCXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp)

find_package(Crow REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC Crow::Crow ${OpenCV_LIBRARIES})
