cmake_minimum_required(VERSION 3.10)
project(HardLinkCopier)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(HardLinkCopier
    src/main.cpp
    src/copy_files.cpp
    src/create_links.cpp
)