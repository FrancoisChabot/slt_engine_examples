add_executable(01_hello_world
  main.cpp)

target_link_libraries(01_hello_world slt_core)

set_target_properties(01_hello_world PROPERTIES FOLDER "01_hello_world")
