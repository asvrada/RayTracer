//
// Created by WuZiJie on 23/10/2016.
//

#ifndef RAYTRACING_LIGHT_HPP
#define RAYTRACING_LIGHT_HPP

#include "Math.hpp"

class Light {
public:
    glm::vec3 origin;
    glm::vec3 color;
    float intensity;

    Light() : intensity(100) {}

    Light(glm::vec3 origin) : Light() {
        this->origin = origin;
    }

    Light(glm::vec3 origin, glm::vec3 color) : Light(origin) {
        this->color = color;
    }
};

#endif //RAYTRACING_LIGHT_HPP
