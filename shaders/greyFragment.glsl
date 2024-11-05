  #version 330 core

  in vec3 fragNormal;  // Normal from vertex shader
  in vec3 fragPos;     // Position from vertex shader

  out vec4 frag_colour;  // Output color
  uniform vec3 lightPosition; // Light position in world space
  uniform vec3 lightColor;    // Light color

  void main() {
     // Ambient light component
    vec3 ambient = 0.2 * lightColor;

     // Diffuse light component
     vec3 norm = normalize(fragNormal);
     vec3 lightDir = normalize(lightPosition - fragPos);
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = diff * lightColor;

    // Final color: ambient + diffuse with grey tone
     vec3 resultColor = (ambient + diffuse) * vec3(0.5);  // grey color
     frag_colour = vec4(resultColor, 1.0);
  }