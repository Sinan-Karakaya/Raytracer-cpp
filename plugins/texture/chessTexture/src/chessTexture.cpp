/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** chessTexture
*/

#include "chessTexture.hpp"
#include "Tools.hpp"

namespace RayTracer {
    ChessTexture::ChessTexture() {};

    ChessTexture::~ChessTexture() {};

    const ITexture *ChessTexture::getColorA() const
    {
        return _colorA;
    }

    const ITexture *ChessTexture::getColorB() const
    {
        return _colorB;
    }

    const Math::Vector3D ChessTexture::textureColorAt(const Math::Vector3D &point) const
    {
        double sines = std::sin(10 * point.x) * std::sin(10 * point.y) * std::sin(10 * point.z);

        if (sines < 0)
            return _colorA->textureColorAt(point);
        return _colorB->textureColorAt(point);
    }

    void ChessTexture::builder(const libconfig::Setting &setting)
    {
        Tools tools;
        std::string type = setting["type"];
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
    RayTracer::ChessTexture *EntryPoint()
    {
        return new RayTracer::ChessTexture();
    }
}
