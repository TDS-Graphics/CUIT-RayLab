//
// Created by brownie on 2026/5/16.
//

#include "Scene.hpp"
#include "MathHelper.hpp"

Intersection Sphere::Intersect(const Ray &ray) const
{
    Intersection hit;

    Vector3 OC = ray.origin - this->center;
    float a = Vector3::dot(ray.dir, ray.dir);
    float b = 2.0f * Vector3::dot(OC, ray.dir);
    float c = Vector3::dot(OC, OC) - this->radius * this->radius;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return hit;
    }

    float t = (-b - std::sqrt(discriminant)) / (2 * a);
    if (t < EPSILON)
    {
        t = (-b + std::sqrt(discriminant)) / (2 * a);
    }
    if (t < EPSILON)
    {
        return hit;
    }

    hit.happened = true;
    hit.distance = t;
    hit.position = ray.origin + ray.dir * t;
    hit.normal = GetNormal(hit.position, *this);
    hit.obj = const_cast<Sphere*>(this);

    return hit;
}

Intersection Scene::Intersect(const Ray &ray) const
{
    Intersection closest;
    closest.distance = std::numeric_limits<float>::max();

    for (const auto& sphere : spheres)
    {
        Intersection hit = sphere.Intersect(ray);

        if (hit.happened && hit.distance < closest.distance)
        {
            closest = hit;
        }
    }

    return closest;
}
