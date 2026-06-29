cmake_minimum_required(VERSION 4.0)
project(CUIT_RayLab)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(CUIT_RayLab src/main.cpp
        src/Vector.cpp
        src/Renderer.cpp
        include/Renderer.hpp
        src/Color.cpp
        include/Color.hpp
        src/Scene.cpp
        src/MathHelper.cpp
        include/MathHelper.hpp
        src/Ray.cpp
        include/Ray.hpp
        src/Intersection.cpp
        include/Intersection.hpp
)
