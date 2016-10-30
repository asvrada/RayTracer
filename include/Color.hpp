//
// Created by WuZiJie on 30/10/2016.
//

#ifndef RAYTRACING_COLOR_HPP
#define RAYTRACING_COLOR_HPP

#include "Math.hpp"

class Color {
public:
    // specular value
    float P;

    glm::vec3 baseColor;
    glm::vec3 specularColor;
    glm::vec3 ambientColor;

    Color() : P(10) {

    }

    // Constructor
    Color(float P, const glm::vec3 &baseColor,
          const glm::vec3 &specularColor, const glm::vec3 &ambientColor) :
            P(P),
            baseColor(baseColor),
            specularColor(specularColor),
            ambientColor(ambientColor) {}
};

#endif //RAYTRACING_COLOR_HPP
