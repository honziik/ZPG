#version 330 core

out vec4 FragColor;  // Finální barva fragmentu

in vec3 FragPos;     // Pozice fragmentu ve světových souřadnicích
in vec3 Normal;      // Normála fragmentu

uniform vec3 lightColor;  // Barva světla světlušky

void main()
{
    FragColor = vec4(0.8,1.0,0.0, 1.0); 
}