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

//Prototypes

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
    
	// diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
	// specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine results - ambient and diffuse are the same
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
    
	// diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
	// specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
	// attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    
	// combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
	ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    
	return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	    vec3 lightDir = normalize(light.position - FragPos);
		//Diffuse shading calculations	
		float diff = max(dot(normal, lightDir), 0.0);
	
		//Specular shading calculations	
		vec3 reflectDir = normalize(reflect(-lightDir, normal));  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

		//attenuation
		float dist = length(light.position - fragPos);
		float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist*dist));

		//spotlight intesity 
		float theta = dot(lightDir, normalize(-light.direction));
		float epsilon = light.cutoff - light.outerCutoff;
		float intensity = clamp((theta-light.outerCutoff) / epsilon, 0.0, 1.0);
	
		//combine calculations
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  

		ambient *= attenuation*intensity;
		diffuse *= attenuation*intensity;
		specular *= attenuation*intensity;

		return (ambient + diffuse + specular);
}


void main()
{ 
	// properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 color = CalculateDirectionalLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < numPointLights; i++)
        color += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: Spot light
    color += CalculateSpotLight(spotLight, norm, FragPos, viewDir);    
    
    FragColor = vec4(color, 1.0);
};