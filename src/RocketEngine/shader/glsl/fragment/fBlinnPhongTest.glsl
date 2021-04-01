#version 330 core
out vec4 FragColor;

struct Material {
	sampler2D diffuse, specular;
    float shininess;
}; 

struct DirectionalLight {
	vec3 direction, ambient, diffuse, specular;
};

struct PointLight {
	vec3 position, ambient, diffuse, specular;
	float constant, linear, quadratic;
};
#define MAX_NUM_POINT_LIGHTS 30

struct SpotLight {
	vec3 position;
	vec3 direction; 
	float cutoff, outerCutoff;
    vec3 ambient, diffuse, specular;
	float constant, linear, quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform int numPointLights; //number of point lights in use
uniform vec3 viewPos;
uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[MAX_NUM_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform sampler2D texture1;
uniform bool blinn;


void main()
{ 
	vec3 color = texture(texture1, TexCoords).rgb;
    // ambient
    vec3 ambient = pointLights[0].ambient * color;
    // diffuse
    vec3 lightDir = normalize(pointLights[0].position - FragPos);
    
    vec3 normal = normalize(Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 specular = vec3(0);
    
    if(!blinn)
    {
        spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        specular = vec3(0.3) * spec; // assuming bright white light color
    }
    else
    {
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess*2);
        specular = vec3(0.3) * spec; // assuming bright white light color
    }
    
    FragColor = vec4(ambient + diffuse + specular, 1.0);
};