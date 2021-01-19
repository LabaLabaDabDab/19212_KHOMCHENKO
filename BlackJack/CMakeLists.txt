cmake_minimum_required(VERSION 3.17)
project(BlackJack2)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)

include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

add_executable(BlackJack2 blackjack.h blackjack.cpp main.cpp difficult.h difficult.cpp dominatestrategy.cpp dominatestrategy.h enums.h exception.h factory.h FirstStr.h FirstStr.cpp game.cpp game.h gui.h gui.cpp multistr.cpp multistr.h otherstr.h otherstr.cpp secondstr.cpp secondstr.h strategy.h StrategyImp.h Tests.cpp)

target_link_libraries(BlackJack2 gtest gtest_main)
target_link_libraries(BlackJack2 gmock gmock_main)