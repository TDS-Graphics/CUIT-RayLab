#include <iostream>
#include "../include/Vector.hpp"
#include "../include/Scene.hpp"
#include "../include/Renderer.hpp"

int main()
{
    std::cout << "==========================================================\n";
    std::cout << "            Welcome to CUIT Graphics Course Lab!          \n";
    std::cout << "==========================================================" << std::endl;

    Scene scene;

    scene.MakeSphere({-1, 0, 3}, 1.0f, Color{100, 120, 140}, 0.3f, 0.1f);
    scene.MakeSphere({4, -100.5, 5}, 100.0f, Color{240, 235, 225}, 0.3f, 0.1f);
    scene.MakeSphere({1.75, 0.3, 4}, 1.0f, Color{220, 180, 140}, 0.8f, 0.1f);

    PointLight light1;
    light1.position = Vector3{5, 4, 3};
    light1.color = Color{255, 255, 255};
    scene.point_lights.push_back(light1);

    Renderer::Draw(scene, 1920, 1080, 65);
    return 0;
}
