/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** metal
*/

#include "Metal.hpp"

namespace RayTracer::Plugin {
    Metal::Metal(const Math::Vector3D &albedo, double fuzz) : _albedo(albedo)
    {
        if (fuzz < 1)
            _fuzz = fuzz;
        else
            _fuzz = 1;
    }

    void Metal::init(const libconfig::Setting &setting)
    {
        Math::Vector3D albedo = Math::Vector3D(setting["material"]["color"]["r"],
                                                    setting["material"]["color"]["g"],
                                                    setting["material"]["color"]["b"]);
        double fuzz = setting["material"]["fuzz"];
        _albedo = albedo;
        _fuzz = fuzz;
    }
};

extern "C" {
    RayTracer::AMaterial *EntryPoint()
    {
        return new RayTracer::Plugin::Metal();
    }
}
