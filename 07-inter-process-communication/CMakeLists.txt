cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(07-inter-process-communication)

include_directories(include)

add_executable(shm_example
  src/shm_example.c
)

add_executable(msg_example
  src/msg_example.c
)