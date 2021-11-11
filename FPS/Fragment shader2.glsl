#version 450

#define MAX_POINT_LIGHTS 10

struct LightPoint {
	vec3 position;
	vec3 diffuse;
	vec3 specular;
	float linear;
	float quadratic;
} ;

struct LightDirect {

	vec3 diffuse;
	vec3 specular;
	vec3 direction;
};

struct MaterialStruct {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

in vec2 TexCor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform vec3 ambient;

uniform int MaxPointLight;
uniform MaterialStruct material;
uniform LightDirect DirectLight;
uniform LightPoint PointLight[MAX_POINT_LIGHTS];

out vec4 resultColor;

vec3 calculateDirectionalLight(LightDirect directLight, vec3 normal, vec3 viewDir){
	vec3 lightDir = normalize(-directLight.direction);
	
	float diff = max(dot(normal, lightDir), 0.0);
	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
	vec3 diffuse = directLight.diffuse * diff * vec3(texture(material.diffuse, TexCor));
	vec3 specular = directLight.specular * spec *vec3(texture(material.specular, TexCor));
	
	return diffuse + specular;
}

vec3 calculatePointLight(LightPoint light, vec3 normal, vec3 viewDir, vec3 fragPos){

	 vec3 lightDir = normalize(light.position - fragPos);
    // диффузное освещение
    float diff = max(dot(normal, lightDir), 0.0);
    // освещение зеркальных бликов
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // затухание
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (1 + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // комбинируем результаты
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCor));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCor));
    diffuse  *= attenuation;
    specular *= attenuation;
    return (diffuse + specular);
}


void main()
{

	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 totalLight = ambient * vec3(texture(material.diffuse, TexCor));
	totalLight = totalLight + calculateDirectionalLight(DirectLight, normal, viewDir);

	for (int i = 0; i < MaxPointLight; i++){
		totalLight = totalLight + calculatePointLight(PointLight[i], normal, viewDir, FragPos);
	}

    vec3 color = totalLight;
	
	//if (TexCor.x < -1.f){
        resultColor = vec4(color, 1.f);
    //} else {
      //  resultColor = texture(tex, TexCor) * vec4(color, 1.f);
    //}
    // Выходной цвет = цвету текстуры в указанных UV-координатах
    
}
