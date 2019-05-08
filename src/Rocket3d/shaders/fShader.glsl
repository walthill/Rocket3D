#version 330 core

out vec4 fragColor;

in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//vec3 white = vec3(1.0, 1.0, 1.0);
	//fragColor = vec4(ourColor, 1.0);

	//The output of this fragment shader is then the (filtered) color of the texture at the (interpolated) texture coordinate.
	//fragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0);
	fragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.05); 
};