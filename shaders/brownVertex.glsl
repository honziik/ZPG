#version 330 core

layout(location = 0) in vec3 vp;  // Vertex position
layout(location = 1) in vec3 vn;  // Vertex normal
layout(location = 2) in vec2 uv;  // UV souřadnice

out vec2 fragUV;  // UV souřadnice předané do fragment shaderu

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    fragUV = uv;  // Předání UV souřadnic
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}
