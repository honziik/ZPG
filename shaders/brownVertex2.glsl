#version 330 core

layout(location = 0) in vec3 vp;  // Vertex position
layout(location = 1) in vec3 vn;  // Vertex normal
layout(location = 2) in vec2 uv;  // UV souřadnice

out vec2 fragUV;  // UV souřadnice předané do fragment shaderu
out vec3 fragNormal; 
out vec3 fragPos; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    vec4 worldPosition = modelMatrix * vec4(vp, 1.0);
    fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;
    fragPos =   vec3(worldPosition.xyz / worldPosition.w);
    fragUV = uv;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}
