/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** StripTexture
*/

#ifndef STRIPTEXTURE_HPP_
    #define STRIPTEXTURE_HPP_

    #include "SolidColor.hpp"

namespace RayTracer {
    class StripTexture : public ATexture {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new Strip Texture object
             * Create a grid texture with two colors
             * @param colorA The color of the first square
             * @param colorB The color of the second square
             */
            StripTexture();

            /**
             * @brief Destroy the Strip Texture object
             *
             */
            ~StripTexture() override;

            ///////////////////////
            // Setters & Getters //
            ///////////////////////

            /**
             * @brief Get the first color of the strip texture
             *
             * @return ITexture * The first color
             */
            ITexture *getColorA() const;

            /**
             * @brief Get the second color of the strip texture
             *
             * @return ITexture * The second color
             */
            ITexture *getColorB() const;

            const Math::Vector3D textureColorAt(const Math::Vector3D &point) const override;

            void builder(const libconfig::Setting &settings) override;

        private:
            // The first color of the strip texture
            ITexture *_colorA;
            // The second color of the strip texture
            ITexture *_colorB;
    };
};

#endif /* !STRIPTEXTURE_HPP_ */
