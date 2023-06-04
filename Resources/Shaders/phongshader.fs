#version 330 core

in vec3 vColor;
in vec3 vNormal;
in vec3 vFragPos;

uniform vec3 uLightPosition;
uniform vec3 uLightAmbient;
uniform vec3 uLightDiffuse;
uniform vec3 uViewPos;
uniform vec3 uLightColor; // new uniform variable

out vec4 FragColor;

void main()
{
    // ambient
    vec3 ambient = uLightAmbient * vColor * uLightColor;
  	
    // diffuse 
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightPosition - vFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uLightDiffuse * diff * vColor * uLightColor;
    
    // specular
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = uLightDiffuse * spec * vColor * uLightColor;  
        
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}