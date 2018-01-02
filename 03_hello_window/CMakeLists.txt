add_executable(03_hello_window
  main.cpp)

#Backend selection is done by choosing which slt_runtime library to link against
target_link_libraries(03_hello_window slt_runtime_glfw )

set_target_properties(03_hello_window PROPERTIES FOLDER "03_hello_window")
