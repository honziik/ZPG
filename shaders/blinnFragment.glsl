#version 330 core

in vec3 fragNormal;   // Normála interpolovaná z vertex shaderu
in vec3 fragPos;      // Pozice fragmentu v prostoru světa

out vec4 frag_colour; // Výstupní barva fragmentu

// Uniformy pro světla
uniform int numLights; // Počet světel

struct Light {
    vec3 position;  // Pozice světla nebo směr pro DirectionalLight
    vec3 color;     // Barva světla
    int type;       // Typ světla: 0 = PointLight, 1 = DirectionalLight, 2 = Spotlight
    vec3 direction; // Pouze pro Directional a Spotlight
    float innerCutoff; // Pouze pro Spotlight
    float outerCutoff; // Pouze pro Spotlight
    float constant; // Attenuace pro PointLight
    float linear;   // Attenuace pro PointLight
    float quadratic; // Attenuace pro PointLight
};

uniform Light lights[10]; // Pole světel (maximálně 10 světel)
uniform vec3 viewPos;     // Pozice kamery

void main() {
    vec3 resultColor = vec3(0.0); // Akumulovaná barva všech světel
    vec3 norm = normalize(fragNormal); // Normalizace normály
    vec3 viewDir = normalize(viewPos - fragPos); // Směr kamery

    for (int i = 0; i < numLights; i++) {
        vec3 lightDir;
        float attenuation = 1.0; // Výchozí hodnota attenuace
        float distance = 0.0;

        // Výpočet světla podle typu
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

        // Ambientní složka
        vec3 ambient = 0.1 * lights[i].color;

        // Difuzní složka
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;

        // Spekulární složka (Blinn-Phong model)
        vec3 halfwayDir = normalize(lightDir + viewDir); // Halfway vektor
        float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0); // Exponent pro lesk
        vec3 specular = spec * lights[i].color;

        // Aplikace attenuace
        diffuse *= attenuation;
        specular *= attenuation;

        // Přidání výsledku tohoto světla
        resultColor += (ambient + diffuse + specular);
    }

    frag_colour = vec4(resultColor, 1.0); // Výstupní barva fragmentu
}
