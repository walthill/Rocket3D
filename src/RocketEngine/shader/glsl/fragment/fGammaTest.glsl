#version 330 core
out vec4 FragColor;

struct Material {
	sampler2D diffuse, specular;
    float shininess;
}; 

struct PointLight {
	vec3 position, ambient, diffuse, specular;
};
#define MAX_NUM_POINT_LIGHTS 30


in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform int numPointLights; //number of point lights in use
uniform vec3 viewPos;
uniform Material material;
uniform PointLight pointLights[MAX_NUM_POINT_LIGHTS];
uniform sampler2D texture1;
uniform float gamma; 
uniform bool gammaCorrected; 

vec3 BlinnPhong(vec3 normal, vec3 fragPos, vec3 lightPos, vec3 lightColor)
{
    // diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fragPos);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * lightColor;    

    // simple attenuation
    float max_distance = 1.5;
    float dist = length(lightPos - fragPos);

    //NOTE:  no need for the constant linear and quadratic factors anymore
    float attenuation = 1.0 / (gammaCorrected ? dist * dist : dist);
    
    diffuse *= attenuation;
    specular *= attenuation;
    
    return diffuse + specular;
}


void main()
{ 
	vec3 color = texture(texture1, TexCoords).rgb;
    vec3 lighting = vec3(0.0);

    lighting += BlinnPhong(normalize(Normal), FragPos, pointLights[0].position, pointLights[0].ambient);

    color *= lighting;

    if(gammaCorrected)
        color = pow(color, vec3(1.0/gamma));

    FragColor = vec4(color, 1.0);
};