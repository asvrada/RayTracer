//
// Created by WuZiJie on 23/10/2016.
//

#include <iostream>
#include <memory>
#include <vector>
#include "include/Sphere.hpp"
#include "include/Ray.hpp"
#include "include/Light.hpp"

//Third-party library for writing PNG
#include "PngWriter.hpp"
#include "include/Math.hpp"


#define MAX_DEPTH 3
#define BG_COLOR vec3(0, 0, 0)

using namespace std;

using glm::vec3;
using glm::dot;

class Camera {
public:
    // position in the world
    vec3 origin;
private:
    // Coord system based on camera
    vec3 u, v, w;
    // distance from image plane
    float d;
    // height and width of the image plane
    int height, width;
    //left right top bottom
    int l, r, t, b;

public:
    Camera() : u(vec3(1, 0, 0)), v(vec3(0, 1, 0)), w(vec3(0, 0, -1)) {
        d = 300.0f;
    }

    Camera(int width, int height) : Camera() {
        setScreenResolution(width, height);
    }

    Camera &setOrigin(vec3 newOrigin) {
        this->origin = newOrigin;
        return *this;
    }

    Camera &setScreenResolution(int width, int height) {
        this->width = width;
        this->height = height;

        d = width / 2;
        l = -width / 2;
        r = -l;
        t = height / 2;
        b = -t;
        return *this;
    }

    /**
     * Generate Ray based on the index i and j
     * (0, 0) is at the left bottom of the image
     * @param i index alone x axis
     * @param j index alone y axis
     * @return vector3 pointing from origin to the point(i, j)
     */
    Ray generateRay(int i, int j) {
        float u = (float) (l + (r - l) * (i + 0.5) / width);
        float v = (float) (b + (t - b) * (j + 0.5) / height);

        return Ray(origin, this->w * -d + this->u * u + this->v * v);
    }
};

///////////
// Codes //
///////////

//Objects
vector<shared_ptr<Surface>> objects;
// Light
vector<Light> lights{Light(vec3(-300, 200, 0)), Light(vec3(500, 400, -200))};


vec3 AmbientShading(float intensity, const HitResult &hitResult) {
    return clamp_color(hitResult.hitObject->color.ambientColor * intensity);
}

// Lambertian
vec3 LambertianShading(const Light &light, const HitResult &hitResult) {
    vec3 directionTowardsLight = normalize(light.origin - hitResult.hitPoint);

    float multiply = light.intensity / pow((light.origin - hitResult.hitPoint).length(), 2)
                     * max(0.0f, dot(hitResult.n, directionTowardsLight));
    return clamp_color(hitResult.hitObject->color.baseColor * multiply);
}

// Blinn-Phong Model
vec3 BlinnPhongShading(const Light &light, const HitResult &hitResult, const vec3 &viewPosition) {
    vec3 directionTowardsLight = normalize(light.origin - hitResult.hitPoint);
    vec3 directionTowardsView = normalize(viewPosition - hitResult.hitPoint);

    vec3 h = normalize(directionTowardsView + directionTowardsLight);

    float multiply = light.intensity / pow((light.origin - hitResult.hitPoint).length(), 2)
                     * pow(max(0.0f, dot(hitResult.n, h)), hitResult.hitObject->color.P);

    return clamp_color(hitResult.hitObject->color.specularColor * multiply);
}

Ray computeReflectionRay(vec3 direction, vec3 normal, vec3 hitPoint) {
    vec3 r = normalize(direction - normal * dot(direction, normal) * 2.0f);

    return Ray(hitPoint + r * 0.1f, r);
}

vec3 Trace(const Ray &primeRay, int DEPTH) {
    HitResult hitResult;
    hitResult.t = std::numeric_limits<float>::max();

    // Find hit
    for (auto each:objects) {
        HitResult result = each->hit(primeRay);
        if (result.isHit) {
            // closer to camera
            if (result.t > 0 && result.t < hitResult.t) {
                hitResult = result;
            }
        }
    }

    // No hit, return background color
    if (!hitResult.isHit) {
        return BG_COLOR;
    }

    vec3 reflectionColor;
    // Compute reflection ray
    // And refraction ray
    if (DEPTH < MAX_DEPTH) {
        Ray reflectionRay = computeReflectionRay(primeRay.direction, hitResult.n, hitResult.hitPoint);
        reflectionColor = clamp_color(Trace(reflectionRay, DEPTH + 1) * 0.5f);
    }

    // normal way
    vec3 color = AmbientShading(1, hitResult);
    for (auto light : lights) {
        bool inShadow = false;

        vec3 tmp_direction = normalize(light.origin - hitResult.hitPoint);
        Ray shadowRay(hitResult.hitPoint + tmp_direction * 0.1f, tmp_direction);
        for (auto each:objects) {
            auto result = each->hit(shadowRay);
            if (result.isHit && result.t > 0) {
                inShadow = true;
                break;
            }
        }

        if (inShadow) {
            continue;
        }

        color += LambertianShading(light, hitResult) + BlinnPhongShading(light, hitResult, primeRay.origin);
    }

    return clamp_color(color + reflectionColor);
}

int main() {
    int WIDTH = 800;
    int HEIGHT = 600;
    // Camera
    Camera camera(WIDTH, HEIGHT);

    // Sphere
    Sphere bottomWall(vec3(0, -100000130, 0), 100000000);
    Sphere sphere1(vec3(-100, 0, 400), 100);
    sphere1.color.baseColor = vec3(180, 128, 128);
    sphere1.color.specularColor = vec3(50);
    sphere1.color.P = 80;

    objects.push_back(make_shared<Sphere>(sphere1));
    sphere1.center.x = 100;
    sphere1.center.z = 550;
    objects.push_back(make_shared<Sphere>(sphere1));
    objects.push_back(make_shared<Sphere>(bottomWall));

    PngWriter png(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // Generate Ray
            Ray currentRay = camera.generateRay(x, y);

            // Lets trace!
            vec3 color = Trace(currentRay, 0);

            png.set(x, y, (unsigned char) color.x, (unsigned char) color.y, (unsigned char) color.z);
        }
    }

    png.write("out/sample.png");
    return 0;
}