cmake_minimum_required(VERSION 3.10)
project(SlayTheSpireLite)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES "*.cpp")

add_executable(SlayTheSpireLite ${SOURCES})
