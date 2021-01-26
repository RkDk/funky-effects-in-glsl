
#version 410 core
in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D textureId;

void main() {
  fragColor = texture(textureId, texCoord);
}
