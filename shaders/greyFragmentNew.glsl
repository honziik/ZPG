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

// Uniform pro kameru
uniform vec3 viewPos; // Pozice kamery

void main() {
    vec3 resultColor = vec3(0.0); // Akumulovaná barva všech světel

    for (int i = 0; i < numLights; i++) {
        vec3 ambient = 0.02 * lights[i].color;

        vec3 lightDir;
        float distance = 0.0;
        float attenuation = 1.0;

        if (lights[i].type == 0) { // PointLight
            // Bodové světlo: směr světla je od pozice světla k pozici fragmentu
            lightDir = normalize(lights[i].position - fragPos);
            distance = length(lights[i].position - fragPos); // Vzdálenost mezi fragmentem a světlem
            // Attenuace: 1 / (constant + linear * d + quadratic * d^2)
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);
        } else if (lights[i].type == 1) { // DirectionalLight
            lightDir = normalize(-lights[i].direction);
        } else if (lights[i].type == 2) { // Spotlight
            lightDir = normalize(lights[i].position - fragPos);
	}
            
       
        // Difuzní složka
        vec3 norm = normalize(fragNormal);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lights[i].color;
	if(lights[i].type == 2){
        	float dot_product = dot(lightDir, normalize(-lights[i].direction));
           	float alpha = cos(radians(lights[i].outerCutoff));
            	if (dot_product < alpha) {
                	attenuation = 0;
            	}else {
                	attenuation *= clamp((dot_product - alpha) / (1 - alpha), 0.0, 1.0);
            	}
	}
        // Spekulární složka
        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
        vec3 specular = spec * lights[i].color;

        // Aplikace attenuace na všechny složky
        diffuse *= attenuation;
        specular *= attenuation;

        // Kombinace složek
        resultColor += (ambient + diffuse + specular);
    }

    frag_colour = vec4(resultColor * vec3(0.5), 1.0); // Výstupní barva
}
