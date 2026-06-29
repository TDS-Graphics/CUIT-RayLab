//
// Created by brownie on 2026/5/16.
//

#ifndef CUIT_RAYLAB_RENDERER_H
#define CUIT_RAYLAB_RENDERER_H
#include "Scene.hpp"

class Renderer
{
public:
    static void Draw(Scene& scene, int width, int height, float fov);
};

#endif //CUIT_RAYLAB_RENDERER_H
