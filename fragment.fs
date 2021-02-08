
#version 410 core
in vec2 oTexCoord;
flat in int oWavyFactor;

out vec4 fragColor;

uniform sampler2D textureId;

void main() {
  vec2 updatedTexCoord = oWavyFactor == 0? oTexCoord : oTexCoord + (vec2(0,.02)) * sin((oWavyFactor* 0.0174533f)+(oTexCoord.x*30));
  fragColor = texture(textureId, updatedTexCoord);
}
