#version 330 core

out vec4 FragColor;  // final color

in vec3 FragPos; 
in vec3 Normal;  

uniform vec3 lightColor; 

void main()
{
    FragColor = vec4(0.8,1.0,0.0, 1.0); 
}