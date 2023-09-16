/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** GradientColor
*/

#ifndef GRADIENTCOLOR_HPP_
    #define GRADIENTCOLOR_HPP_

    #include "ATexture.hpp"

namespace RayTracer {
    class GradientColor : public ATexture {
        public:
            /**
             * @brief Construct a new Gradient Texture object
             * Create a gradient texture with the given colors
             * @param colorA The first gradient color
             * @param colorB The second gradient color
             */
            GradientColor();

            /**
             * @brief Destroy the Ring Texture object
             *
             */
            ~GradientColor() override;

            /**
             * @brief Get the first color of the chess texture
             *
             * @return const Math::Vector3d The first color
             */
            const Math::Vector3D getColorA() const;

            /**
             * @brief Get the second color of the chess texture
             *
             * @return const Math::Vector3d The second color
             */
            const Math::Vector3D getColorB() const;

            /**
             * @brief Get the color at the position
             *
             * @param point The point to get the color
             * @return const Math::Vector3D The color at the given point
             */
            const Math::Vector3D textureColorAt(const Math::Vector3D &point) const override;

            void builder(const libconfig::Setting &settings) override;

        private:
            // The first color of the gradient
            Math::Vector3D _colorA;
            // The second color of the gradient
            Math::Vector3D _colorB;
    };
};

#endif /* !GRADIENTCOLOR_HPP_ */
