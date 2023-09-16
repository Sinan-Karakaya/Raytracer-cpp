/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** GradientColor
*/

#include "GradientColor.hpp"

namespace RayTracer {
    GradientColor::GradientColor() : ATexture() {};

    GradientColor::~GradientColor() {};

    const Math::Vector3D GradientColor::getColorA() const
    {
        return _colorA;
    }

    const Math::Vector3D GradientColor::getColorB() const
    {
        return _colorB;
    }

    const Math::Vector3D GradientColor::textureColorAt(const Math::Vector3D &point) const
    {
        Math::Vector3D newColor = _colorB - _colorA;

        double fraction = point.x - std::floor(point.x);

        return _colorA + newColor * fraction;
    }

    void GradientColor::builder(const libconfig::Setting &setting)
    {
        _colorA = Math::Vector3D(setting["colorA"]["r"], setting["colorA"]["g"], setting["colorA"]["b"]);
        _colorB = Math::Vector3D(setting["colorB"]["r"], setting["colorB"]["g"], setting["colorB"]["b"]);
    }
};

extern "C" {
    RayTracer::GradientColor *EntryPoint()
    {
        return new RayTracer::GradientColor();
    }
}
