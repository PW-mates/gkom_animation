#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrColor;
layout (location = 2) in vec3 attrNormal;

uniform mat4 uProjectionMatrix;
uniform mat4 uCameraMatrix;
uniform mat4 uModelMatrix;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
};
uniform PointLight uLight;

uniform vec3 uViewPos;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos;
out vec3 ViewPos;

void main()
{
    vec4 worldPosition = uModelMatrix * vec4(attrPosition, 1.0);
    gl_Position = uProjectionMatrix * uCameraMatrix * worldPosition;
    FragPos = worldPosition.xyz;
    Normal = mat3(transpose(inverse(uModelMatrix))) * attrNormal;
    LightPos = uLight.position;
    ViewPos = uViewPos;
}