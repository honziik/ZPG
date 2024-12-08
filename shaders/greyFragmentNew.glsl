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

    for(int i = 0; i < numLights; i++) {
        vec3 ambient = 0.02 * lights[i].color;

        vec3 lightDir;
        float distance = 0.0;
        float attenuation = 1.0;

        if(lights[i].type == 0) { // PointLight
            lightDir = normalize(lights[i].position - fragPos);
            distance = length(lights[i].position - fragPos); 
            // Attenuace: 1 / (constant + linear * d + quadratic * d^2)
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);
        } else if(lights[i].type == 1) { // DirectionalLight
            lightDir = normalize(-lights[i].direction);
        } else if(lights[i].type == 2) { // Spotlight
            lightDir = normalize(lights[i].position - fragPos);
        }

        // Difusse
        vec3 norm = normalize(fragNormal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;
        if(lights[i].type == 2) {
            float dot_product = dot(lightDir, normalize(-lights[i].direction));
            float alpha = cos(radians(lights[i].outerCutoff));
            if(dot_product < alpha) {
                attenuation = 0;
            } else {
                attenuation *= clamp((dot_product - alpha) / (1 - alpha), 0.0, 1.0);
            }
        }
        // Specular
        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        vec3 specular = spec * lights[i].color;


        diffuse *= attenuation;
        specular *= attenuation;

        resultColor += (ambient + diffuse + specular);
    }

    frag_colour = vec4(resultColor * vec3(0.5), 1.0);
}
