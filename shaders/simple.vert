#version 430

uniform mat4 PM, VM, TG;

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

out vec3 FragPosition;
out vec3 FragNormal;
out vec2 FragTexcoord;

void main() {	
  FragPosition = vertex;
  FragNormal   = normal;
  FragTexcoord = texcoord;

	gl_Position = PM * VM * TG * vec4(vertex, 1.0);
}
