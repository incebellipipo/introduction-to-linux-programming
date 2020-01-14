cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(00-introduction)

include_directories(include)

add_executable(arguments 
  src/arguments.c
)

add_executable(errno
  src/errno.c
)

add_executable(std-descriptors
  src/std-descriptors.c
)

add_executable(memory-allocation
  src/memory-allocation.c
)
