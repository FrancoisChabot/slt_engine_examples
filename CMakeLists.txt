cmake_minimum_required(VERSION 3.1)

project(slt_engine_examples)

find_package(slt_engine REQUIRED)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

IF(MSVC)
  add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
ENDIF(MSVC)

add_subdirectory(01_hello_world)
add_subdirectory(02_simple_file_read)
add_subdirectory(03_hello_window)
add_subdirectory(04_resources)
add_subdirectory(05_gui)
add_subdirectory(06_sound)
