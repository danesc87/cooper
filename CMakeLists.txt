cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project("Cooper")

include_directories(${PROJECT_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 11)

add_executable(main src/main.cpp)
target_link_libraries(main sqlite3)

enable_testing()
add_subdirectory(test)
