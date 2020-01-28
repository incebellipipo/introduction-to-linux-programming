cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(03-reverse-shell)

add_executable(reverse-shell
  src/reverse-shell.c
)
