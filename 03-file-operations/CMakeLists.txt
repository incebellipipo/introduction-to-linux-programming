cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 11)

project(fio)

# include_directories(include)

# add_library(lib${PROJECT_NAME}-dev src/${PROJECT_NAME}/${PROJECT_NAME}.cpp)
# target_link_libraries(lib${PROJECT_NAME}-dev)

add_executable(cat src/cat.c)
add_executable(random src/random.c)

configure_file(src/read-this.txt ${CMAKE_BINARY_DIR} COPYONLY)
