//
// Created by WuZiJie on 23/10/2016.
//

#ifndef RAYTRACING_SURFACE_HPP
#define RAYTRACING_SURFACE_HPP

class Ray;
class HitResult;

class Surface {
public:
    // specular value
    float P;

    glm::vec3 color;
    glm::vec3 specularColor;
    glm::vec3 ambientColor;

    virtual HitResult hit(const Ray &) = 0;
};

#endif //RAYTRACING_SURFACE_HPP
