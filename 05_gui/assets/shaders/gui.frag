#version 420

layout(binding=0) uniform sampler2D tex;

in vec4 out_color;
in vec2 out_uv;

out vec4 result_col;

void main() {
  vec4 tex = texture(tex, out_uv);
  result_col = vec4(out_color.xyz, tex.x);
}
