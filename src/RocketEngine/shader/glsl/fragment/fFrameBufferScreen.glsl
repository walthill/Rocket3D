#version 330 core
out vec4 fragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
    fragColor = vec4(col, 1.0);
} 

/*
ImGui render texture doesn't allow for frambebuffer post processing :(
#version 330 core
out vec4 fragColor;

in vec2 TexCoords;

uniform float gamma;
uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
    vec3 gammaCorrection =  pow(col, vec3(1.0/gamma));
    fragColor = vec4(gammaCorrection, 1.0);
} 
*/