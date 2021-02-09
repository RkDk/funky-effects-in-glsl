
#version 410 core
in vec2 oTexCoord;

out vec4 fragColor;

uniform sampler2D textureId;

void main() {
  fragColor = texture(textureId, oTexCoord);
}
