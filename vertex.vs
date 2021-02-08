#version 410 core
layout (location=0) in vec2 pos;
layout (location=1) in vec2 texCoord;

out vec2 oTexCoord;
flat out int oWavyFactor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform int wavyFactor;

void main() {
  gl_Position = projection * view * model * vec4(pos, 1, 1);
  oTexCoord = texCoord;
  oWavyFactor = wavyFactor;
}
