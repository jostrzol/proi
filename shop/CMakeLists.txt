file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(shop ${SRC})

target_include_directories(shop INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})