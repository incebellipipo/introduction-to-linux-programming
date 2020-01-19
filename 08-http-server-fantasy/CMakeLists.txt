cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(08-http-server-fantasy)

include_directories(include)

add_library(fantasy_server
  src/fantasy_server/fantasy_server.c
)

target_link_libraries(fantasy_server
  pthread
)

add_executable(server
  src/fantasy_server/server.c
)

target_link_libraries(server
  fantasy_server
)