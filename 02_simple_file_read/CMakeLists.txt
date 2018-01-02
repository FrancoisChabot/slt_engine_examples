add_executable(02_simple_file_read
  main.cpp)

target_link_libraries(02_simple_file_read slt_core)

set_target_properties(02_simple_file_read PROPERTIES FOLDER "02_simple_file_read")
