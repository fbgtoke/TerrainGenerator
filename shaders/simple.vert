#version 430

layout(location = 0)uniform mat4 PM;
layout(location = 1)uniform mat4 VM;
layout(location = 2)uniform mat4 TG;
layout(location = 3)uniform mat4 parentTG;

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

	gl_Position = PM * VM * parentTG * TG * vec4(vertex, 1.0);
}
