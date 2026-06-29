//
// Created by brownie on 2026/5/17.
//

#ifndef CUIT_RAYLAB_INTERSECTION_HPP
#define CUIT_RAYLAB_INTERSECTION_HPP

#include "Vector.hpp"
#include <limits>

class Sphere;

struct Intersection
{
    bool happened = false;
    Vector3 position{};
    Vector3 normal{};
    float distance = std::numeric_limits<float>::max();
    Sphere* obj = nullptr;
};

#endif //CUIT_RAYLAB_INTERSECTION_HPP
