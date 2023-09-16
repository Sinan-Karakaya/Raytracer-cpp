/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** SolidColor
*/

#ifndef SOLIDCOLOR_HPP_
    #define SOLIDCOLOR_HPP_

    #include "ATexture.hpp"

namespace RayTracer {
    class SolidColor : public ATexture {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new SolidColor Texture object
             * Create a solid color texture
             * @param color The color of the texture
             */
            SolidColor(Math::Vector3D color) : ATexture(), _color(color) {};

            /**
             * @brief Destroy the Strip Texture object
             *
             */
            ~SolidColor() override {};

            ///////////////////////
            // Setters & Getters //
            ///////////////////////

            /**
             * @brief Get the color of the texture
             *
             * @return const Math::Vector3D The color of the texture
             */
            const Math::Vector3D getColor() const
            {
                return _color;
            }

            /////////////
            // Methods //
            /////////////

            /**
             * @brief get the color at the given point of the texture
             *
             * @param point The point to get the color
             * @return const Math::Vector3D The color at the given point
             */
            const Math::Vector3D textureColorAt(const Math::Vector3D &point) const override
            {
                (void)point;

                return _color;
            }

            void builder(const libconfig::Setting &setting) override
            {
                (void)setting;
            }

        private:
            // The color of the Texture
            Math::Vector3D _color;
    };
};

#endif /* !SOLIDCOLOR_HPP_ */
