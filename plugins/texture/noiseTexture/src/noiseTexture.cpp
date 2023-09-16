/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** noiseTexture
*/

#include "noiseTexture.hpp"
#include "APrimitive.hpp"
#include "Tools.hpp"

namespace RayTracer {
    NoiseTexture::NoiseTexture() : ATexture() {};

    NoiseTexture::~NoiseTexture() {};

    Math::PerlinNoise NoiseTexture::getNoise() const
    {
        return _noise;
    }

    ITexture *NoiseTexture::getTexture() const
    {
        return _texture;
    }

    const Math::Vector3D NoiseTexture::textureColorAt(const Math::Vector3D &point) const
    {
        Math::Vector3D noisePoint(
            _noise.noise(point),
            _noise.noise(point + Math::Vector3D(-0.5f, 0.2f, 0.1f)),
            _noise.noise(point + Math::Vector3D(0.3f, 0.4f, -0.4f))
        );

        return point + noisePoint;
    }

    void NoiseTexture::builder(const libconfig::Setting &settings)
    {
        Tools tools;
        std::string type = settings["type"];
        if (type == "solidColor")
            _texture = new SolidColor(Math::Vector3D(settings["texture"]["color"]["r"], settings["texture"]["color"]["g"], settings["texture"]["color"]["b"]));
        else
            _texture = tools.loadTexture(settings["texture"]);
    }
};

extern "C" {
    RayTracer::NoiseTexture *EntryPoint()
    {
        return new RayTracer::NoiseTexture();
    }
}
