/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** ITexture
*/

#ifndef ITEXTURE_HPP_
    #define ITEXTURE_HPP_

    #include "Matrix.hpp"
    #include "Vector3D.hpp"
    #include <libconfig.h++>
    #include "LibLoader.hpp"
    #include <unistd.h>

namespace RayTracer {
    class ITexture {
        public:
            virtual ~ITexture() = default;

            // Getter & Setters
            virtual Math::Matrix getTextureMatrix() const = 0;
            virtual void setTextureMatrix(const Math::Matrix Matrix) = 0;

            // Methods
            virtual const Math::Vector3D colorAt(const Math::Vector3D &point) const = 0;
            virtual const Math::Vector3D textureColorAt(const Math::Vector3D &point) const = 0;

            // Factory
            virtual void builder(const libconfig::Setting &setting) = 0;

    };
};

#endif /* !ITEXTURE_HPP_ */
