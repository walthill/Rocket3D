#version 330 core
out vec4 fragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{    
    vec4 texColor = texture(texture1, TexCoords);
    if(texColor.a < 0.1)
        discard;
    fragColor = texColor;
}