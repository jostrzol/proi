cmake_minimum_required(VERSION 3.10)

project(DIY-Shop-Simulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(FLAGS -Wall -Wextra -Wno-unknown-pragmas -Wno-pmf-conversions)
add_compile_options(${FLAGS})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(shop)
list(APPEND EXTRA_LIBS shop)

file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(simulator ${SRC})

target_link_libraries(simulator PUBLIC ${EXTRA_LIBS} pthread)

add_subdirectory(config)
