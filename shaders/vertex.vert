#version 130

in vec3 in_position;
in vec3 in_color;

out vec3 frag_color;

uniform mat4 TG;
uniform mat4 VM;
uniform mat4 PM;

void main()  {
	frag_color = in_color;

    gl_Position = PM * VM * TG * vec4 (in_position, 1.0);
}