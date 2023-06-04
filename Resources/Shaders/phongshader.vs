#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrColor;
layout (location = 2) in vec3 attrNormal;

uniform mat4 uProjectionMatrix;
uniform mat4 uCameraMatrix;
uniform mat4 uModelMatrix;
uniform vec3 uLightPosition;

out vec3 vColor;
out vec3 vNormal;
out vec3 vFragPos;

void main()
{
    vColor = attrColor;
    vNormal = attrNormal;
    vFragPos = vec3(uModelMatrix * vec4(attrPosition, 1.0));
    gl_Position = uProjectionMatrix * uCameraMatrix * uModelMatrix * vec4(attrPosition, 1.0);
}