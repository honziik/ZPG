#version 330 core
layout(location = 0) in vec3 vp;  // Vertex position
layout(location = 1) in vec3 vn;  // Vertex normal

out vec3 fragPos;   // Fragment position (to pass to fragment shader)
out vec3 fragNormal;  // Normal (to pass to fragment shader)

uniform mat4 modelMatrix;      // Model transformation matrix
uniform mat4 viewMatrix;       // View (camera) transformation matrix
uniform mat4 projectionMatrix; // Projection matrix (perspective or orthographic)

void main() {
     fragNormal = mat3(transpose(inverse(modelMatrix))) * vn;  // Transform normal to world space
     fragPos = vec3(modelMatrix * vec4(vp, 1.0));  // Transform vertex position to world space
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);  // Final transformed position
}