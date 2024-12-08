#version 330 core

in vec3 fragNormal;
in vec3 fragPos;

out vec4 frag_colour;

void main() {
        vec3 color = normalize(fragNormal) * 0.5 + 0.5;
        frag_colour = vec4(color, 1.0);
}