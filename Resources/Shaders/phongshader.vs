#version 330 core

layout (location = 0) in vec3 attrPosition;
layout (location = 1) in vec3 attrColor;
layout (location = 2) in vec3 attrNormal;

uniform mat4 uProjectionMatrix;
uniform mat4 uCameraMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uLightPosition;
uniform mat4 uLightAmbient;
uniform mat4 uLightDiffuse;

out vec3 vColor;
out vec3 vPosition;

void main()
{
    vColor = attrColor;

    vPosition = (uProjectionMatrix * uCameraMatrix * uModelMatrix * vec4(attrPosition, 1.0)).xyz;

    gl_Position = uProjectionMatrix * uCameraMatrix * uModelMatrix * vec4(attrPosition, 1.0);
}