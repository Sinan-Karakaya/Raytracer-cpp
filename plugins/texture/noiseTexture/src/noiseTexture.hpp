/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** noiseTexture
*/

#ifndef NOISETEXTURE_HPP_
    #define NOISETEXTURE_HPP_

    #include "ATexture.hpp"
    #include "PerlinNoise.hpp"

namespace RayTracer {
    class NoiseTexture : public ATexture {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new Noise Texture object
             *
             */
            NoiseTexture();

            /**
             * @brief Destroy the Noise Texture object
             *
             */
            ~NoiseTexture() override;

            /**
             * @brief Get the Noise object
             *
             * @return Math::PerlinNoise The noise
             */
            Math::PerlinNoise getNoise() const;

            /**
             * @brief Get the Texture object of the noise
             *
             * @return ITexture * The texture of the noise
             */
            ITexture *getTexture() const;

            /**
             * @brief Get the color of the noise at the given point
             *
             * @param point The point to get the color
             * @return const Math::Vector3D The color at the given point
             */
            const Math::Vector3D textureColorAt(const Math::Vector3D &point) const override;

            void builder(const libconfig::Setting &settings) override;

        private:
            // The noise
            Math::PerlinNoise _noise;
            // The texture we put on the noise
            ITexture *_texture;
    };
};

#endif /* !NOISETEXTURE_HPP_ */
