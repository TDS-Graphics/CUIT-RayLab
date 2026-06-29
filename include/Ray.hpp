//
// Created by brownie on 2026/5/17.
//

#ifndef CUIT_RAYLAB_RAY_HPP
#define CUIT_RAYLAB_RAY_HPP

#include <Vector.hpp>

struct Ray
{
    Vector3 origin;
    Vector3 dir;
    float t;
};

#endif //CUIT_RAYLAB_RAY_HPP
