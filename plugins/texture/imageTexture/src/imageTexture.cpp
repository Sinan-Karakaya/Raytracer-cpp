/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** imageTexture
*/

#include "imageTexture.hpp"

namespace RayTracer {
    ImageTexture::ImageTexture() : ATexture(), _data(nullptr), _width(0), _height(0), _bytes_per_scanline(0) {}

    ImageTexture::~ImageTexture()
    {
        if (_data)
            delete _data;
    }

    const Math::Vector3D ImageTexture::textureColorAt(const Math::Vector3D &point) const
    {
        int i = 0;
        int j = 0;

        if (_data == nullptr)
            return Math::Vector3D(0.0f, 1.0f, 1.0f);

        double u = point.x - std::floor(point.x);
        double v = point.y - std::floor(point.y);

        i = static_cast<int>(u * _width);
        j = static_cast<int>(v * _height);

        if (i >= _width)
            i = _width - 1;
        if (j >= _height)
            j = _height - 1;

        const double color_scale = 1.0f / 255.0f;
        unsigned char *pixel = _data + j * _bytes_per_scanline + i * BYTES_PER_PIXEL;

        return Math::Vector3D(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
    }

    void ImageTexture::builder(const libconfig::Setting &settings)
    {
        int components_per_pixel = BYTES_PER_PIXEL;

        const char *filepath = settings["filepath"];
        if (!(_data = stbi_load(filepath, &_width, &_height, &components_per_pixel, components_per_pixel))) {
            std::cerr << "ERROR: Could not load texture image file '" << filepath << "'.\n";
            _width = 0;
            _height = 0;
        }

        _bytes_per_scanline = BYTES_PER_PIXEL * _width;
    }
};

extern "C" {
    RayTracer::ImageTexture *EntryPoint()
    {
        return new RayTracer::ImageTexture();
    }
}
