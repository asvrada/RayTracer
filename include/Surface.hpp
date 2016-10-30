//
// Created by WuZiJie on 23/10/2016.
//

#ifndef RAYTRACING_SURFACE_HPP
#define RAYTRACING_SURFACE_HPP

#include "Color.hpp"

// Forward declaration
class Ray;

class HitResult;

class Surface {
public:
    Color color;

    virtual HitResult hit(const Ray &) = 0;
};

#endif //RAYTRACING_SURFACE_HPP
