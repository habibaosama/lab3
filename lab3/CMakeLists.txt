cmake_minimum_required(VERSION 3.22)
project(lab3 C)

set(CMAKE_C_STANDARD 11)

include_directories(lab3_starter_code)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

add_executable(lab3
        lab3_starter_code/caltrain-runner.c
        lab3_starter_code/caltrain.c
        lab3_starter_code/caltrain.h)
target_link_libraries(lab3 PRIVATE Threads::Threads)