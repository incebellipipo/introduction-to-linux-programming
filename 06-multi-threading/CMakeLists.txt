cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(06-multi-threading)

include_directories(include)

add_executable(sample1
  src/sample1.c
)

target_link_libraries(sample1 pthread)

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