#version 330 core
out vec4 fragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
    fragColor = vec4(col, 1.0);
} 