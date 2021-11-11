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

void main()
{

    resultColor = texture(material.diffuse, TexCor) * vec4(1,1,1,0.1);
	//color = vec4(outColor, 1.0f);
}