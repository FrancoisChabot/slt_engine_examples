add_executable(05_gui
  main.cpp)

slt_build_assets(
  05_gui_res  #The name of the build target associated with this resource build
  assets/init.json  #The root asset registry
  init              #The in-engine name of the registry
)

target_link_libraries(05_gui slt_runtime_glfw)

#Make the executable target be dependant on the assets build
add_dependencies(05_gui 05_gui_res)

set_target_properties(05_gui PROPERTIES FOLDER "05_gui")
set_target_properties(05_gui_res PROPERTIES FOLDER "05_gui")
