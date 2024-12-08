#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <stdexcept>
#include "Transform.h"

class BezierMove : public Transform {
public:
    BezierMove(const std::vector<glm::vec3>& controlPoints, float speed)
        : controlPoints(controlPoints), speed(speed) {
        if (controlPoints.size() < 4 || (controlPoints.size() - 1) % 3 != 0) {
            throw std::invalid_argument("Number of control points must be 4 + 3n (n >= 0).");
        }
        initializeSegments();
    }

    glm::mat4 getMatrix() const override {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        t += deltaTime * speed;

        // Pøechod mezi segmenty
        while (t > 1.0f) {
            t -= 1.0f;
            currentSegment = (currentSegment + 1) % segments.size();
        }

        // Vypoèet aktuální pozice na aktuálním segmentu
        glm::vec3 position = computeBezierPoint(t, segments[currentSegment]);
        return glm::translate(glm::mat4(1.0f), position);
    }

private:
    struct Segment {
        glm::vec3 p0, p1, p2, p3;
    };

    std::vector<glm::vec3> controlPoints;
    float speed;
    mutable float lastTime = 0.0f;
    mutable float t = 0.0f;
    mutable size_t currentSegment = 0;
    std::vector<Segment> segments;

    void initializeSegments() {
        for (size_t i = 0; i + 3 < controlPoints.size(); i += 3) {
            segments.push_back({ controlPoints[i], controlPoints[i + 1], controlPoints[i + 2], controlPoints[i + 3] });
        }
    }

    glm::vec3 computeBezierPoint(float t, const Segment& segment) const {
        glm::mat4 A = glm::mat4(glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
            glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
            glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));

        glm::mat4x3 B = glm::mat4x3(segment.p0, segment.p1, segment.p2, segment.p3);

        glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);

        return parameters * A * glm::transpose(B);
    }
};
