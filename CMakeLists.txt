cmake_minimum_required(VERSION 3.22)
project(MCTS)

set(CMAKE_CXX_STANDARD 14)
add_executable(tictaetoe example/tictaetoe/main.cpp example/tictaetoe/TicTaeToe.cpp example/tictaetoe/TTTmcts.cpp)
