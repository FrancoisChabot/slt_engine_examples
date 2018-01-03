add_executable(06_sound
  main.cpp)

slt_build_assets(
  06_sound_res  #The name of the build target associated with this resource build
  assets/init.json  #The root asset registry
  init              #The in-engine name of the registry
)

target_link_libraries(06_sound slt_runtime_glfw)

#Make the executable target be dependant on the assets build
add_dependencies(06_sound 06_sound_res)

set_target_properties(06_sound PROPERTIES FOLDER "06_sound")
set_target_properties(06_sound_res PROPERTIES FOLDER "06_sound")
