#version 430

uniform sampler2D tex;

layout(location = 0) uniform vec3 lightDir;

in vec3 FragPosition;
in vec3 FragNormal;
in vec2 FragTexcoord;

layout(location = 0) out vec4 outColor;

void main() {
  float cosTheta = clamp(dot(FragNormal, -lightDir), 0, 1);
  vec4 texcolor = texture(tex, FragTexcoord);

  if (texcolor.w < 0.5)
    discard;

  outColor = texcolor * cosTheta;
  //outColor = vec4(texcolor);
}