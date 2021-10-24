
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // TODO: Replace with your code...
    // If gl_Position was set correctly, this gives a totally red cube
    float ambientStrength = 0.1;
    vec3 ambientColor = ambientStrength * lightColor;
    
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diffuseScalar = max(dot(norm, lightDir), 0.0);
    vec3 diffuseColor = lightColor * diffuseScalar;
    
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float specularScalar = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specularColor = specularStrength * specularScalar * lightColor;

    vec3 result = (ambientColor + diffuseColor + specularColor) * objectColor;

    color = vec4(result, 1.0f);
} 
