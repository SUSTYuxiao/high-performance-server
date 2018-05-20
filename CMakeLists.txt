cmake_minimum_required(VERSION 3.10)
project(high_performance_server C)

set(CMAKE_C_STANDARD 99)

add_executable(high_performance_server main.c tool.c tool.h thread_pool.c thread_pool.h)