add_executable(04_resources
  main.cpp)


slt_build_assets(
  04_resources_res  #The name of the build target associated with this resource build
  assets/main.json  #The root asset registry
  main              #The in-engine name of the registry
)

target_link_libraries(04_resources slt_runtime_glfw)

#Make the executable target be dependant on the assets build
add_dependencies(04_resources 04_resources_res)

set_target_properties(04_resources PROPERTIES FOLDER "04_resources")
set_target_properties(04_resources_res PROPERTIES FOLDER "04_resources")
