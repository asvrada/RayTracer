//
// Created by WuZiJie on 23/10/2016.
//

#ifndef RAYTRACING_RAY_HPP
#define RAYTRACING_RAY_HPP

#include <ostream>
#include "Math.hpp"

class Ray {
public:
    glm::vec3 origin;
    glm::vec3 direction;
    // Length
    float t;

public:
    Ray() {
        t = 0;
    }

    Ray(const glm::vec3 &origin, const glm::vec3 &direction) : origin(origin), direction(glm::normalize(direction)) {
        t = 0;
    }

    // output stream
    friend std::ostream &operator<<(std::ostream &os, const Ray &ray) {
        os << "Ray:"
           << "\n\tOrigin: " << ray.origin.x << " " << ray.origin.y << " " << ray.origin.z
           << "\n\tDirection: " << ray.direction.x << " " << ray.direction.y << " " << ray.direction.z
           << "\n\tT: " << ray.t;

        return os;
    }

    glm::vec3 getHitPoint() {
        return origin + direction * t;
    }

    glm::vec3 getHitPoint(float t) {
        this->t = t;
        return getHitPoint();
    }
};

#endif //RAYTRACING_RAY_H
