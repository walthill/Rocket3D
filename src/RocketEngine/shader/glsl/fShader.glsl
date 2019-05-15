#version 330 core

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	vec3 white = vec3(1.0, 0.5, 0.31);
	fragColor = vec4(lightColor*objectColor, 1.0);
};