cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(05-multi-threading)

include_directories(include)


add_executable(mutex_example
  src/mutex_example.c
)
target_link_libraries(mutex_example pthread)

add_executable(simple_multi_threading
  src/simple_multi_threading.c
)
target_link_libraries(simple_multi_threading 
  pthread
)

add_executable(func_pointer_threading
  src/func_pointer_threading.c
)
target_link_libraries(func_pointer_threading
  pthread
  m
)
