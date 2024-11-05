#version 330 core

in vec3 fragNormal;   // Normal interpolated from the vertex shader
in vec3 fragPos;      // Position of the fragment in world space

out vec4 frag_colour; // Final output color

uniform vec3 lightPosition; // Position of the light in world space
uniform vec3 lightColor;    // Color of the light
uniform vec3 viewPos;       // Position of the camera in world space

void main() {
    vec3 norm = normalize(fragNormal);                     // Normalize the normal vector
    vec3 lightDir = normalize(lightPosition - fragPos);    // Calculate the light direction
    vec3 viewDir = normalize(viewPos - fragPos);           // Calculate the view direction

    // Diffuse component using Lambert's model
    float diff = max(dot(norm, lightDir), 0.0); // Calculate the diffuse factor
    vec3 diffuse = diff * lightColor * vec3(0.4, 0.6, 0.8); // Light blue color

    // Specular component (Blinn-Phong model)
    vec3 halfwayDir = normalize(lightDir + viewDir); // Calculate the halfway vector
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0); // Calculate the specular factor
    vec3 specular = spec * lightColor; // Calculate the specular color

    frag_colour = vec4(diffuse + specular, 1.0); // Output the final color
}
