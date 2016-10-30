//
// Created by WuZiJie on 23/10/2016.
//

#ifndef RAYTRACING_MATH_HPP
#define RAYTRACING_MATH_HPP

#include <glm/glm.hpp>
#include <cmath>
#include <memory>

float clamp(float value, float min, float max) {
    return std::min(std::max(value, min), max);
}

// To clamp color
glm::vec3 clamp(const glm::vec3 &value, float min, float max) {
    return glm::vec3(clamp(value.x, min, max), clamp(value.y, min, max), clamp(value.z, min, max));
}

glm::vec3 clamp_color(const glm::vec3 value) {
    return clamp(value, 0, 255);
}

class Surface;

/*
 * HitResult
 * Used to store results like where is the hitpoint
 */

typedef struct HitResult {
    bool isHit = false;

    // hit ray
    float t = -1;
    glm::vec3 hitPoint;
    //Normal of the hit point
    glm::vec3 n;
    //the object we hit
    Surface *hitObject = nullptr;

    ~HitResult() {
        hitObject = nullptr;
    }
} HitResult;

#endif //RAYTRACING_MATH_H
