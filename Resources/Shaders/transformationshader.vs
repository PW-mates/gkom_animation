#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrColor;

out vec3 vColor;

uniform mat4 uProjectionMatrix;
uniform mat4 uCameraMatrix;
uniform mat4 uModelMatrix;

void main()
{
    vColor = attrColor;

    gl_Position = uProjectionMatrix * uCameraMatrix * uModelMatrix * vec4(attrPosition, 1.0);
}