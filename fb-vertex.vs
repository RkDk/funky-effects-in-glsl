#version 410 core
layout (location=0) in vec2 pos;
layout (location=1) in vec2 texCoord;

out vec2 oTexCoord;

void main() {
  gl_Position = vec4(2,2,1,1) * (vec4(-.5,-.5,0,0) + vec4(pos, 1, 1));
  oTexCoord = texCoord;
}
