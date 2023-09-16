/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** BlendedTexture
*/

#include "BlendedTexture.hpp"
#include "Tools.hpp"

namespace RayTracer {
    BlendedTexture::BlendedTexture() : ATexture() {};

    BlendedTexture::~BlendedTexture() {};

    const ITexture *BlendedTexture::getTextureA() const
    {
        return _textureA;
    }

    const ITexture *BlendedTexture::getTextureB() const
    {
        return _textureB;
    }

    const Math::Vector3D BlendedTexture::textureColorAt(const Math::Vector3D &point) const
    {
        Math::Vector3D colorA = _textureA->textureColorAt(point);
        Math::Vector3D colorB = _textureB->textureColorAt(point);

        return colorA.blend(colorB);
    }

    void BlendedTexture::builder(const libconfig::Setting &setting)
    {
        Tools tools;
        std::string type = setting["type"];
        if (type == "texture") {
            std::string nameA = setting["textureA"]["name"];
            std::string nameB = setting["textureB"]["name"];
            if (nameA == "solidColor")
                _textureA = new SolidColor(Math::Vector3D(setting["textureA"]["color"]["r"], setting["textureA"]["color"]["g"], setting["textureA"]["color"]["b"]));
            else
                _textureA = tools.loadTexture(setting["textureA"]);
            if (nameB == "solidColor")
                _textureB = new SolidColor(Math::Vector3D(setting["textureB"]["color"]["r"], setting["textureB"]["color"]["g"], setting["textureB"]["color"]["b"]));
            else
                _textureB = tools.loadTexture(setting["textureB"]);
        }
        else {
            _textureA = new SolidColor(Math::Vector3D(0.0f, 0.0f, 0.0f));
            _textureB = new SolidColor(Math::Vector3D(0.0f, 0.0f, 0.0f));
        }
    }
};

extern "C" {
    RayTracer::ITexture *EntryPoint()
    {
        return new RayTracer::BlendedTexture();
    }
}
