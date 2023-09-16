/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** RingTexture
*/

#include "RingTexture.hpp"
#include "Tools.hpp"

namespace RayTracer {
    RingTexture::RingTexture() : ATexture() {};

    RingTexture::~RingTexture() {};

    const ITexture *RingTexture::getColorA() const
    {
        return _colorA;
    }

    const ITexture *RingTexture::getColorB() const
    {
        return _colorB;
    }

    const Math::Vector3D RingTexture::textureColorAt(const Math::Vector3D &point) const
    {
        double newPoint = (point - Math::Vector3D(0.0f, 0.0f, 0.0f)).length();

        if ((int)std::floor(newPoint) % 2 == 0)
            return _colorA->textureColorAt(point);
        return _colorB->textureColorAt(point);
    }

    void RingTexture::builder(const libconfig::Setting &setting)
    {
        std::string type = setting["type"];
        Tools tools;
        if (type == "color") {
            Math::Vector3D colorA = Math::Vector3D(setting["colorA"]["r"], setting["colorA"]["g"], setting["colorA"]["b"]);
            Math::Vector3D colorB = Math::Vector3D(setting["colorB"]["r"], setting["colorB"]["g"], setting["colorB"]["b"]);
            _colorA = new SolidColor(colorA);
            _colorB = new SolidColor(colorB);
        }
        if (type == "texture") {
            std::string nameA = setting["textureA"]["name"];
            std::string nameB = setting["textureB"]["name"];
            if (nameA == "solidColor")
                _colorA = new SolidColor(Math::Vector3D(setting["textureA"]["color"]["r"], setting["textureA"]["color"]["g"], setting["textureA"]["color"]["b"]));
            else
                _colorA = tools.loadTexture(setting["textureA"]);
            if (nameB == "solidColor")
                _colorB = new SolidColor(Math::Vector3D(setting["textureB"]["color"]["r"], setting["textureB"]["color"]["g"], setting["textureB"]["color"]["b"]));
            else
                _colorB = tools.loadTexture(setting["textureB"]);
        }
        else {
            _colorA = new SolidColor(Math::Vector3D(0.0f, 0.0f, 0.0f));
            _colorB = new SolidColor(Math::Vector3D(0.0f, 0.0f, 0.0f));
        }
    }
};

extern "C" {
    RayTracer::RingTexture *EntryPoint()
    {
        return new RayTracer::RingTexture();
    }
}
