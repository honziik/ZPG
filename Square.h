#pragma once
const float square[] = {
    -50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,  // levý dolní roh (normála smìøuje nahoru, y=1)
     50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,  // pravý dolní roh (normála smìøuje nahoru, y=1)
    -50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,  // levý horní roh (normála smìøuje nahoru, y=1)

    // Druhý trojúhelník
    -50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f,  // levý horní roh (normála smìøuje nahoru, y=1)
     50.0f, 0.0f, -50.0f,  0.0f, 1.0f, 0.0f,  // pravý dolní roh (normála smìøuje nahoru, y=1)
     50.0f, 0.0f,  50.0f,  0.0f, 1.0f, 0.0f
};
