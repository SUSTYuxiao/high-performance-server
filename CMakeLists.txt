cmake_minimum_required(VERSION 3.10)
project(high_performance_server C)

set(CMAKE_C_STANDARD 99)

add_executable(high_performance_server main.c px_tool.c px_tool.h px_thread_pool.c px_thread_pool.h px_epoll.c px_epoll.h px_request.c px_request.h px_timer.c px_timer.h px_priority_queue.c px_priority_queue.h)