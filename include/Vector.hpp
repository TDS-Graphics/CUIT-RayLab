//
// Created by brownie on 2026/5/15.
//

#ifndef CUIT_RAYLAB_VECTOR_H
#define CUIT_RAYLAB_VECTOR_H

#include <cmath>

/*
 * 数学库 vector.h
 *
 * 你需要在这里实现一系列三维向量运算：
 * 1. 加法和减法
 * 2. 标量乘法
 * 3. 数量积
 * 4. 向量积
 * 5. 向量求模和归一化
 */

class Vector3
{
public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& v) const
    {
        return Vector3{x + v.x, y + v.y, z + v.z};
    }

    Vector3 operator-(const Vector3& v) const
    {
        return Vector3{x - v.x, y - v.y, z - v.z};
    }

    Vector3 operator*(float lambda) const
    {
        return Vector3{x * lambda, y * lambda, z * lambda};
    }

    static float norm(const Vector3 &v)
    {
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    static float dot(const Vector3 &v1, const Vector3 &v2)
    {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    static Vector3 cross(const Vector3 &v1, const Vector3 &v2)
    {
        return Vector3
        {
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        };
    }

    static Vector3 normalize(const Vector3 &v)
    {
        float norm = Vector3::norm(v);
        return {v.x / norm, v.y / norm, v.z / norm};
    }
};

#endif //CUIT_RAYLAB_VECTOR_H
