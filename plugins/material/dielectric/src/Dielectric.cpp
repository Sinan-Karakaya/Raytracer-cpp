/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Dielectric
*/

#include "Dielectric.hpp"

namespace RayTracer::Plugin {
    Dielectric::Dielectric(double ref_idx) : _ref_idx(ref_idx) {}

    Dielectric::~Dielectric() {}

    double Dielectric::schlick(double cosine, double ref_idx) const
    {
        double r0 = (1.0f - ref_idx) / (1.0f + ref_idx);

        r0 = r0 * r0;

        return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
    }

    void Dielectric::init(const libconfig::Setting &setting)
    {
        _ref_idx = setting["material"]["refIdx"];
    }
};

extern "C" {
    RayTracer::AMaterial *EntryPoint()
    {
        return new RayTracer::Plugin::Dielectric();
    }
}
