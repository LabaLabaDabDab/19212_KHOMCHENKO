cmake_minimum_required(VERSION 3.17)
project(BlackJack)

set(CMAKE_CXX_STANDARD 14)

add_executable(BlackJack main.cpp BlackJack.h deck.cpp deck.h game.cpp game.h SimpledDesk.cpp SimpledDesk.h N_deck.cpp N_deck.h player.cpp player.h)

