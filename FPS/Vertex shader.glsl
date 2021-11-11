#version 450

// ������� ������ ������, ��������� ��� ���� �������� ����� �������
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

    // �������� ������� �������
    gl_Position = projection * view * transform * vec4(position, 1.0f);
   // texCor = textureCoor;

}