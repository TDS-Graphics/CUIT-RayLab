//
// Created by brownie on 2026/5/16.
//

#ifndef CUIT_RAYLAB_COLOR_H
#define CUIT_RAYLAB_COLOR_H

class Color
{
public:
    float r;
    float g;
    float b;

    Color() : r(0), g(0), b(0) {}
    Color(float r, float g, float b) : r(r), g(g), b(b) {}

    static Color Add(const Color &c1, const Color &c2)
    {
        return Color{
            c1.r + c2.r,
            c1.g + c2.g,
            c1.b + c2.b
        };
    }

    static Color Mul(const Color &c1, Color c2)
    {
        return Color{c1.r * c2.r, c1.g * c2.g, c1.b * c2.b};
    }

    static Color MulwithScalar(const Color &c, const float lambda)
    {
        return Color{c.r * lambda, c.g * lambda, c.b * lambda};
    }

    static Color Blend(const Color &c1, const Color &c2, float alpha)
    {
        return Color{
            alpha * c1.r + (1 - alpha) * c2.r,
            alpha * c1.g + (1 - alpha) * c2.g,
            alpha * c1.b + (1 - alpha) * c2.b
        };
    }
};

#endif //CUIT_RAYLAB_COLOR_H
