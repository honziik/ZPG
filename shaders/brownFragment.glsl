#version 330 core

in vec2 fragUV;
out vec4 frag_colour;

uniform sampler2D grassTexture; 

void main() {
    frag_colour = vec4(texture(grassTexture, fragUV).rgb, 1.0);
}
