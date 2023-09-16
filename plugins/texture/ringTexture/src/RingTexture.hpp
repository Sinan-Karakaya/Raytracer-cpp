/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** RingTexture
*/

#ifndef RINGTEXTURE_HPP_
    #define RINGTEXTURE_HPP_

    #include "SolidColor.hpp"

namespace RayTracer {
    class RingTexture : public ATexture {
        public:
            /**
             * @brief Construct a new Ring Texture object
             * Create a ring pattern texture with the given colors
             * @param colorA The first ring color
             * @param colorB The second ring color
             */
            RingTexture();

            /**
             * @brief Destroy the Ring Texture object
             *
             */
            ~RingTexture() override;

            /**
             * @brief Get the first color of the chess texture
             *
             * @return const ITexture * The first color
             */
            const ITexture *getColorA() const;

            /**
             * @brief Get the second color of the chess texture
             *
             * @return const ITexture * The second color
             */
            const ITexture *getColorB() const;

            /**
             * @brief Get the color at the position
             *
             * @param point The point to get the color
             * @return const Math::Vector3D The color at the given point
             */
            const Math::Vector3D textureColorAt(const Math::Vector3D &point) const override;

            void builder(const libconfig::Setting &settings) override;

        private:
            // The first ring color
            ITexture *_colorA;
            // The second ring color
            ITexture *_colorB;
    };
};

#endif /* !RINGTEXTURE_HPP_ */
