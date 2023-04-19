cmake_minimum_required(VERSION 3.25)
project(wcat VERSION 2.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(wcat ./src/wcat_main.cc)
target_compile_options(wcat PRIVATE -O3 -DNDEBUG -Os -Ofast -Og -s -march=native -masm=intel -flto=auto -funroll-all-loops)