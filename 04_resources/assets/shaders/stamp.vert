#version 420

in vec2 slt_vertex;
in vec2 slt_uv;

out vec2 out_uv;

void main() {
  out_uv = slt_uv;
  gl_Position = vec4(slt_vertex, 0, 1);  
}