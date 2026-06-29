//
// Created by brownie on 2026/5/16.
//

#ifndef CUIT_RAYLAB_MATHHELPER_HPP
#define CUIT_RAYLAB_MATHHELPER_HPP

#include "Scene.hpp"
#include <numbers>

constexpr float EPSILON = 0.0001f;

inline float clamp(const float& lower, const float& higher, const float& v)
{
    return std::max(lower, std::min(higher, v));
}

inline float DegreeToRad(float degree)
{
    return degree * std::numbers::pi_v<float> / 180;
}

inline Vector3 GetNormal(const Vector3 &point, const Sphere &sphere)
{
    return Vector3::normalize(point - sphere.center);
}

inline Vector3 GetReflect(const Vector3 &point, const Sphere &sphere)
{
    Vector3 incident = Vector3::normalize(point - Vector3{0,0,0});
    Vector3 normal = GetNormal(point, sphere);
    float NdotL = Vector3::dot(normal, incident);
    return Vector3::normalize(incident - normal * 2 * NdotL);
}

#endif //CUIT_RAYLAB_MATHHELPER_HPP