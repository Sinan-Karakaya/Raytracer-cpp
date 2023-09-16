/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** diffuseLight
*/

#include "diffuseLight.hpp"
#include "SolidColor.hpp"

namespace RayTracer::Plugin {
    diffuseLight::diffuseLight(ITexture *texture) : _emit(texture) {};

    diffuseLight::diffuseLight(const Math::Vector3D &color) : _emit(new SolidColor(color)) {};

    diffuseLight::~diffuseLight()
    {
//        if (_emit)
//            delete _emit;
    }

    void diffuseLight::init(const libconfig::Setting &setting)
    {
        (void)setting;
    }
};

extern "C" {
    RayTracer::AMaterial *EntryPoint()
    {
        return new RayTracer::Plugin::diffuseLight(Math::Vector3D(0.0, 0.0, 0.0));
    }
}
