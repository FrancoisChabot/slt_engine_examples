#version 420

in vec2 slt_vertex;
in vec2 slt_uv;
in vec4 slt_color;

out vec2 out_uv;
out vec4 out_color;

layout (std140) uniform GuiRendering {
  vec2 viewport_size;
};

void main() {
  out_uv = slt_uv;
  out_color = slt_color;

  vec2 half_vp = viewport_size / 2.0;
  gl_Position = vec4((slt_vertex - half_vp) / half_vp, 0.0, 1.0);
}
