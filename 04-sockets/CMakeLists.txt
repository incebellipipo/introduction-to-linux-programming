cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(04-sockets)

add_executable(tcp-server 
  src/samples/tcp-server.c
)

add_executable(tcp-client 
  src/samples/tcp-client.c
)

add_executable(udp-server 
  src/samples/udp-server.c
)

add_executable(udp-client
  src/samples/udp-client.c
)

add_executable(unix-server 
  src/samples/unix-server.c
)

add_executable(unix-client
  src/samples/unix-client.c
)