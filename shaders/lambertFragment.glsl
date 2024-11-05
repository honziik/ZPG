#version 330 core

in vec3 fragNormal;   // Normála interpolovaná z vertex shaderu
in vec3 fragPos;      // Pozice fragmentu v prostoru světa

out vec4 frag_colour; // Výstupní barva fragmentu

uniform vec3 lightPosition; // Pozice světla v prostoru světa
uniform vec3 lightColor;    // Barva světla

void main() {
    vec3 norm = normalize(fragNormal);                  // Normalizace normály
    vec3 lightDir = normalize(lightPosition - fragPos); // Směr světla

    // Ambientní složka
    vec3 ambient = 0.1 * lightColor * vec3(0.4, 0.8, 0.4); // Světle zelená ambientní barva

    // Difuzní složka (Lambertův model)
    float diff = max(dot(norm, lightDir), 0.0);          // Faktor difuzního osvětlení
    vec3 diffuse = diff * lightColor * vec3(0.4, 0.8, 0.4); // Světle zelená difuzní barva

    // Kombinace ambientní a difuzní složky
    vec3 result = ambient + diffuse;
    frag_colour = vec4(result, 1.0); // Výstupní barva fragmentu
}
