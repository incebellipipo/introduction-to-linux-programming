cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(06-multi-threading)

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


# Music maker example
find_package(SDL2)

if(SDL2_LIBRARIES)
    include_directories(${SDL2_INCLUDE_DIRS})
    add_library(musicmaker
        src/musicmaker/sound.c
    )
    target_link_libraries(musicmaker
        pthread
        m
        ${SDL2_LIBRARIES}
    )
    add_executable(composer
        src/musicmaker/composer.c
    )

    target_link_libraries(composer
        musicmaker 
        pthread
    )
else()
    message("sdl2 library can not be found so sound example will not be build")
endif()
