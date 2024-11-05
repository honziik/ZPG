       #version 330 core

       in vec3 fragNormal;  // Normal from vertex shader
       in vec3 fragPos;     // Position from vertex shader

       out vec4 frag_colour;  // Output color

       void main() {
       frag_colour = vec4(0.4f,0.5f,0.12f, 1.0);  
       }