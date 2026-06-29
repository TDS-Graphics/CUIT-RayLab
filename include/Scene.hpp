//
// Created by brownie on 2026/5/15.
//

#ifndef CUIT_RAYLAB_SCENE_H
#define CUIT_RAYLAB_SCENE_H

#include <vector>
#include "Color.hpp"
#include "Intersection.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

class PointLight
{
public:
    Vector3 position{0, 0, 0};
    Color color{255, 255, 255};
};

class Sphere
{
public:
    Vector3 center{0, 0, 0};
    float radius = 0.0f;
    Color diffuse{255, 255, 255};
    float specular = 0.5f;
    float reflectivity = 1.0f;

    [[nodiscard]] Intersection Intersect(const Ray &ray) const;
};

class Scene
{
public:
    std::vector<Sphere> spheres;
    std::vector<PointLight> point_lights;

    [[nodiscard]] Intersection Intersect(const Ray &ray) const;
    void MakeSphere(const Vector3 &center, float radius, const Color& diffuse = Color{255, 255, 255}, 
                   float specular = 0.5f, float reflectivity = 0.0f)
    {
        spheres.push_back(Sphere{center, radius, diffuse, specular, reflectivity});
    }
};

#endif //CUIT_RAYLAB_SCENE_H