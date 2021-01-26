#version 410 core
layout (location=0) in vec2 pos;
layout (location=1) in vec2 _texCoord;

out vec2 texCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
  gl_Position = projection * view * model * vec4(pos, 1, 1);
  texCoord = _texCoord;
}
