cmake_minimum_required(VERSION 3.17)
project(game)

set(CMAKE_CXX_STANDARD 14)

add_executable(game main.cpp game.h deck.h dealer.h factory.h strategy.h settings.h softhand.cpp hardhand.cpp score_17.cpp score_18.cpp score_20.cpp)