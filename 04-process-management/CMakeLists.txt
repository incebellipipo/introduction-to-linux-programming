cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(04-process-management)

include_directories(include)

add_executable(family
  src/family.c
)

add_executable(servant
  src/servant.c
)

add_executable(master-slave
  src/master-slave.c
)

add_executable(signals
  src/signals.c
)

add_executable(piping
  src/piping.c
)

add_executable(signals-with-fork
  src/signals-with-fork.c
)
