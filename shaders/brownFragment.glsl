#version 330 core

in vec2 fragUV;  // Přijímá UV souřadnice z vertex shaderu
out vec4 frag_colour;  // Výstupní barva fragmentu

uniform sampler2D grassTexture;  // Textura trávy

void main() {
    frag_colour = vec4(texture(grassTexture, fragUV).rgb, 1.0);
}
