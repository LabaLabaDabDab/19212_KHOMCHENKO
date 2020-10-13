cmake_minimum_required(VERSION 3.15)
project(untitled7)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/googletest-master)

include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

add_executable(untitled7 main.cpp HashTable.cpp HashTable.h Tests.cpp)

target_link_libraries(untitled7 gtest gtest_main)
target_link_libraries(untitled7 gmock gmock_main)