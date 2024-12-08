#version 330 core

in vec3 fragNormal;
in vec3 fragPos; 

out vec4 frag_colour; 

void main() {
    frag_colour = vec4(0.4f, 0.5f, 0.12f, 1.0); 
}
