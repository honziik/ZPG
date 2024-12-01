#version 330 core

in vec3 fragNormal;   // Normála interpolovaná z vertex shaderu
in vec3 fragPos;      // Pozice fragmentu v prostoru světa

out vec4 frag_colour; // Výstupní barva fragmentu

// Uniformní proměnné pro světlo a kameru
uniform vec3 lightPosition;   // Pozice světla v prostoru světa
uniform vec3 lightColor;      // Barva světla
uniform vec3 viewPos;         // Pozice kamery v prostoru světa

void main() {
    // Ambientní složka
    vec3 ambient = 0.02 * lightColor;

    // Difuzní složka (Lambertův model)
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Spekulární složka (Phongův model)
    vec3 viewDir = normalize(viewPos - fragPos);   // Směr ke kameře
    vec3 reflectDir = reflect(-lightDir, norm);    // Směr odrazu světla
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = spec * lightColor;

    // Výsledná barva: kombinace ambientní, difuzní a spekulární složky
    vec3 resultColor = (ambient + diffuse + specular) * vec3(0.5);  // Šedý tón
    frag_colour = vec4(resultColor, 1.0); // Výstupní barva
}
