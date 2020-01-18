cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(08-http-server-fantasy)

include_directories(include)

add_library(fantasy-server
  src/fantasy-server/fantasy-server.c
)

target_link_libraries(fantasy-server
  pthread
)

add_executable(server
  src/fantasy-server/server.c
)

target_link_libraries(server
  fantasy-server
)