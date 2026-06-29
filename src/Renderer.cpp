//
// Created by brownie on 2026/5/16.
//

#include "Color.hpp"
#include "Renderer.hpp"
#include "MathHelper.hpp"
#include "Ray.hpp"
#include <iostream>

bool IsInShadow(const Vector3& origin, const Vector3& dir, const Scene& scene, float max_distance)
{
    auto shadow_ray = Ray{origin, dir};
    Intersection hit = scene.Intersect(shadow_ray);
    return hit.happened && hit.distance < max_distance;
}

Color SphereShader(const Intersection& hit, const Scene& scene)
{
    Color diffuse_color(hit.obj->diffuse.r / 255.0f,
                        hit.obj->diffuse.g / 255.0f,
                        hit.obj->diffuse.b / 255.0f);

    const float ambient_strength = 0.1f;

    Color final_color = Color::MulwithScalar(diffuse_color, ambient_strength);

    Vector3 view_dir = Vector3::normalize(Vector3{0, 0, 0} - hit.position);

    for (const auto& light : scene.point_lights)
    {
        Vector3 light_dir = light.position - hit.position;
        float distance = Vector3::norm(light_dir);
        light_dir = Vector3::normalize(light_dir);

        if (IsInShadow(hit.position + hit.normal * EPSILON * 2, light_dir, scene, distance))
            continue;

        float diff = std::max(0.0f, Vector3::dot(hit.normal, light_dir));
        Color light_color(light.color.r / 255.0f, light.color.g / 255.0f, light.color.b / 255.0f);
        Color diffuse_component = Color::Mul(Color::MulwithScalar(diffuse_color, diff), light_color);

        Vector3 reflect_dir = Vector3::normalize(GetReflect(hit.position, *hit.obj));
        float spec = std::pow(std::max(0.0f, Vector3::dot(reflect_dir, view_dir)), hit.obj->specular * 100);
        Color specular_component = Color::MulwithScalar(light_color, spec);

        float attenuation = 1.0f / (1.0f + 0.1f * distance + 0.01f * distance * distance);

        Color light_contribution = Color::Add(diffuse_component, specular_component);
        light_contribution = Color::MulwithScalar(light_contribution, attenuation);
        final_color = Color::Add(final_color, light_contribution);
    }

    return final_color;
}

Color CastRay(const Vector3& origin, const Vector3& dir, const Scene& scene, int depth)
{
    int max_depth = 4;

    Intersection hit_payload = scene.Intersect(Ray{origin, dir});
    if (!hit_payload.happened)
    {
        float t = 0.5f * (dir.y + 1.0f);
        Color sky_blue = Color{0.5f, 0.7f, 1.0f};
        Color white = Color{1.0f, 1.0f, 1.0f};
        return Color::Blend(sky_blue, white, t);
    }

    // Let Shader do the job
    Color color = SphereShader(hit_payload, scene);

    if (depth < max_depth && hit_payload.obj->reflectivity > 0.0f)
    {
        Vector3 reflect_dir = GetReflect(hit_payload.position, *hit_payload.obj);
        Color reflect_color = CastRay(
            hit_payload.position + hit_payload.normal * EPSILON * 2,
            reflect_dir,
            scene,
            depth + 1);

        color = Color::Blend(reflect_color, color, hit_payload.obj->reflectivity);
    }
    
    return color;
}

void Renderer::Draw(Scene &scene, int width, int height, float fov)
{
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    Vector3 origin{0, 0, 0};

    std::vector<Color> framebuffer(width * height);

    float tan_half_fov = std::tan(DegreeToRad(fov * 0.5f));

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int bufferIndex = width * i + j;

            float x_normalized = (2.0f * (static_cast<float>(j) + 0.5f) / static_cast<float>(width)) - 1.0f;
            float y_normalized = 1.0f - (2.0f * (static_cast<float>(i) + 0.5f) / static_cast<float>(height));
            float x = x_normalized * aspect * tan_half_fov;
            float y = y_normalized * tan_half_fov;

            Vector3 dir = Vector3::normalize(Vector3(-x, y, 1));

            framebuffer[bufferIndex] = CastRay(origin, dir, scene, 0);
        }
    }

    // 这里直接使用了 GAMES101 光线追踪框架的图像写入实现。
    FILE* fp = fopen("binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", width, height);
    for (auto i = 0; i < height * width; ++i)
    {
        static unsigned char color[3];
        color[0] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].r), 0.6f));
        color[1] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].g), 0.6f));
        color[2] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].b), 0.6f));
        fwrite(color, 1, 3, fp);
    }
    fclose(fp);
}