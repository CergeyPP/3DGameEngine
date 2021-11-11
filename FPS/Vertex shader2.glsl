#version 450

// ¬ходные данные вершин, различные дл€ всех запусков этого шейдера
layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCor;
layout(location = 1) in vec3 normalVec;

out vec2 TexCor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{

    // ¬ыходна€ позици€ вершины
    gl_Position = projection * view * transform * vec4(position, 1.0f);
	FragPos = vec3(transform * vec4(position, 1.f));
    TexCor = texCor;

    Normal = vec3(transform * vec4(normalVec, 0.f));
	

}