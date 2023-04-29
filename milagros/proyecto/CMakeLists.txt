cmake_minimum_required(VERSION 3.15)
project(recordlecture)

set(CMAKE_CXX_STANDARD 14)

add_executable(recordlecture main.cpp record.h avlfile.h libs.h setavlfile.h)