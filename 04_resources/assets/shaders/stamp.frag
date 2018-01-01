#version 420

layout(binding=0) uniform sampler2D tex;

in vec2 out_uv;
out vec4 out_col;

void main() {
  out_col = texture(tex, out_uv);
}