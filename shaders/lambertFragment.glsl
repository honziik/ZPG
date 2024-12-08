#version 330 core

in vec3 fragNormal;
in vec3 fragPos; 

out vec4 frag_colour;

uniform int numLights;

struct Light {
    vec3 position; 
    vec3 color;    
    int type;  
    vec3 direction; 
    float innerCutoff; 
    float outerCutoff;
    float constant;
    float linear;   
    float quadratic; 
};

uniform Light lights[10]; 

uniform vec3 viewPos; 

void main() {
    vec3 resultColor = vec3(0.0);

    vec3 norm = normalize(fragNormal);

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float attenuation = 1.0;
        float distance = 0.0;

        if (lights[i].type == 0) { // PointLight
            lightDir = normalize(lights[i].position - fragPos);
            distance = length(lights[i].position - fragPos);
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);
        } else if (lights[i].type == 1) { // DirectionalLight
            lightDir = normalize(-lights[i].direction);
        } else if (lights[i].type == 2) { // Spotlight
            lightDir = normalize(lights[i].position - fragPos);
            float theta = dot(lightDir, normalize(-lights[i].direction));
            float epsilon = lights[i].outerCutoff - lights[i].innerCutoff;
            float intensity = clamp((theta - lights[i].innerCutoff) / epsilon, 0.0, 1.0);
            attenuation *= intensity;
        }

        vec3 ambient = 0.1 * lights[i].color;

        // Difusse (Lambert model)
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;

        // Specular (shiny surface)
        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        vec3 specular = spec * lights[i].color;

        diffuse *= attenuation;
        specular *= attenuation;

        resultColor += (ambient + diffuse + specular);
    }

    frag_colour = vec4(resultColor, 1.0); 
}
