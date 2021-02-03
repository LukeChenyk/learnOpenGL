#version 330 core
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
  
//uniform vec3 objectColor;
//uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
    //vec3 ambient;
    //vec3 diffuse;
	int useTex0;//使用纹理贴图0
	int useTex1;//使用纹理贴图1
	vec3 color;
	vec3 diffuse;
	sampler2D texture0;
    sampler2D texture1;//高光纹理
    float shininess;
}; 

uniform Material material;

in vec2 TexCoords;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
	 // ambient
    //vec3 ambient = light.ambient * material.color;
	vec3 ambient;
	if(material.useTex0 == 1){
		ambient = light.ambient * vec3(texture(material.texture0, TexCoords));
	} else {
		ambient = light.ambient * material.color;
	}
  	
    // diffuse
	vec3 diffuse;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff * material.diffuse  * light.diffuse;
	if(material.useTex0 == 1){
		diffuse = light.diffuse * diff * vec3(texture(material.texture0, TexCoords));
	}else{
		diffuse = light.diffuse * diff * material.diffuse;
	}

	//specular
	vec3 specular;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	if(material.useTex1 == 1){
		specular = light.specular * spec * vec3(texture(material.texture1, TexCoords));
	}else{
		specular = light.specular * spec;
	}
            
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}