//
// Created by WuZiJie on 23/10/2016.
//

#ifndef RAYTRACING_SPHERE_HPP
#define RAYTRACING_SPHERE_HPP

#include "Math.hpp"
#include "Ray.hpp"
#include "Surface.hpp"

class Sphere : public Surface {
public:
    glm::vec3 center;
    // radius
    float R;

    Sphere(glm::vec3 center, float R) : center(center), R(R) {
        color = glm::vec3(128, 128, 128);
        specularColor = glm::vec3(100, 100, 100);
        ambientColor = glm::vec3(20, 20, 20);
        P = 10;
    }

    HitResult hit(const Ray &ray) override {
        double A = glm::dot(ray.direction, ray.direction);
        double B = glm::dot(ray.direction * 2.0f, ray.origin - center);
        double C = glm::dot(ray.origin - center, ray.origin - center) - R * R;

        HitResult hitResult;
        double sqrtPart = B * B - 4 * A * C;

        if (sqrtPart < 0) {
            hitResult.isHit = false;
            return hitResult;
        };

        sqrtPart = sqrt(sqrtPart);

        double answerOne = (-B + sqrtPart) / (2 * A);
        double answerTwo = (-B - sqrtPart) / (2 * A);

        hitResult.isHit = true;
        hitResult.t = (float) std::min(answerOne, answerTwo);
        hitResult.hitPoint = ray.origin + ray.direction * hitResult.t;
        hitResult.n = glm::normalize(ray.origin + ray.direction * hitResult.t - center);
        hitResult.hitObject = this;

        return hitResult;
    }
};

#endif //RAYTRACING_SPHERE_H
