#version 330 core

in vec3 fragNormal;  // Normála z vertex shaderu
in vec3 fragPos;     // Pozice fragmentu ve světě

out vec4 frag_colour;  // Výstupní barva fragmentu

void main() {
    frag_colour = vec4(0.4f, 0.5f, 0.12f, 1.0);  // Barva objektu
}
