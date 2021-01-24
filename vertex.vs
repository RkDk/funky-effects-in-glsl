#version 410 core
layout (location=0) in vec2 pos;

uniform mat4 projection;
uniform mat4 view;

void main() {
  gl_Position = projection * view * vec4(pos, 1, 1);
}
