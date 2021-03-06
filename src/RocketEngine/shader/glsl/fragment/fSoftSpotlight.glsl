#version 330 core
out vec4 fragColor;

struct Material {
	sampler2D diffuse, specular;
    float shininess;
}; 

struct Light {
	 vec3 position;
	vec3 direction; //directional lighting var
	float cutoff, outerCutoff;
    vec3 ambient, diffuse, specular;
	float constant, linear, quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light; 

void main()
{ 
	//vec3 lightDir = normalize(light.position - FragPos);

	//float theta = dot(lightDir, normalize(-light.direction));
	//float epsilon = light.cutoff - light.outerCutoff;
	//float instensity = clamp((theta-light.outerCutoff) / epsilon, 0.0, 1.0);

	//if(theta > light.cutoff)
	{
		// ambient
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
		// diffuse 
		vec3 norm = normalize(Normal);
	    vec3 lightDir = normalize(light.position - FragPos);
		//vec3 lightDir = normalize(-light.direction);
	
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = normalize(reflect(-lightDir, norm));  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  


		//spotlight (soft edges)
		float theta = dot(lightDir, normalize(-light.direction));
		float epsilon = light.cutoff - light.outerCutoff;
		float intensity = clamp((theta-light.outerCutoff) / epsilon, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity;

		//attenuation
		float dist = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist*dist));

		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		vec3 result = ambient + diffuse + specular;
		fragColor = vec4(result, 1.0);
	}
	//else
	{
		//fragColor = vec4(light.ambient * texture(material.diffuse, TexCoords).rgb, 1.0);
	}
 
};