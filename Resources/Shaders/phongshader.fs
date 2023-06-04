#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material uMaterial;

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
};
uniform PointLight uLight;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;
in vec3 ViewPos;

out vec4 FragColor;

void main()
{
    // Ambient
    vec3 ambient = uMaterial.ambient * uLight.ambient;

    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = uMaterial.diffuse * (diff * uLight.diffuse);

    // Specular 
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), uMaterial.shininess);
    vec3 specular = uMaterial.specular * (spec * uLight.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result * uLight.color, 1.0);
}