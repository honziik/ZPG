#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn; 
layout(location = 2) in vec2 uv; 

out vec2 fragUV;
out vec3 fragNormal; 

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;
    fragUV = uv;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}
