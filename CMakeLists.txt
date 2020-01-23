cmake_minimum_required(VERSION 3.14)
project(Tic_tac_toe)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tic_tac_toe main.cpp Tree.cpp Tree.h Node.cpp Node.h State.cpp State.h)