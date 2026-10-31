cmake_minimum_required(VERSION 3.20)
project(knu_async_dag_v5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

add_executable(work main.cpp)
target_link_libraries(work PRIVATE Threads::Threads)

if(MSVC)
    target_compile_options(work PRIVATE /W4)
else()
    target_compile_options(work PRIVATE -Wall -Wextra -pedantic)
endif()