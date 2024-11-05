        #version 330 core

        in vec3 fragNormal;  // Normal from vertex shader
        in vec3 fragPos;     // Position from vertex shader

        out vec4 frag_colour;  // Output color

        void main() {
        vec3 color = normalize(fragNormal) * 0.5 + 0.5;  // Simple shading
        frag_colour = vec4(color, 1.0);
        }