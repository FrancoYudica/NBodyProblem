cmake_minimum_required(VERSION 3.0)

project(NBody VERSION 0.1)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set (CMAKE_CXX_STANDARD 17)

add_subdirectory(Dependencies)

file(GLOB SRC_H src/*.h)
file(GLOB SRC_CPP src/*.cpp)


add_executable(${PROJECT_NAME} main.cpp ${SRC_H} ${SRC_CPP})

target_include_directories(${PROJECT_NAME} PUBLIC "Dependencies/WolfEngine/Wolf")

target_link_libraries(${PROJECT_NAME} PRIVATE dependencies)

