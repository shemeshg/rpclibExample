cmake_minimum_required(VERSION 3.19)

set (CMAKE_CXX_STANDARD 23)

project(libSMngr VERSION 0.1.0)

enable_testing()

add_subdirectory(libSMngr)
add_subdirectory(main)
add_subdirectory(test)


