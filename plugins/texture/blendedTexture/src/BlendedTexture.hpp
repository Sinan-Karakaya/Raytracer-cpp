/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** BlendedTexture
*/

#ifndef BLENDEDTEXTURE_HPP_
    #define BLENDEDTEXTURE_HPP_

    #include "ATexture.hpp"

namespace RayTracer {
    class BlendedTexture : public ATexture {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new Blender Texture object
             * Create a blender texture with two textures
             * @param textureA The texture of the first square
             * @param textureB The texture of the second square
             */
            BlendedTexture();

            /**
             * @brief Destroy the Blender Texture object
             *
             */
            ~BlendedTexture() override;

            ///////////////////////
            // Setters & Getters //
            ///////////////////////

            /**
             * @brief Get the first texture of the blender texture
             *
             * @return const ITexture * The first texture
             */
            const ITexture *getTextureA() const;

            /**
             * @brief Get the second texture of the blender texture
             *
             * @return const ITexture * The second texture
             */
            const ITexture *getTextureB() const;

            /////////////
            // Methods //
            /////////////

            /**
             * @brief get the color at the given point of the texture
             *
             * @param point The point to get the color
             * @return const Math::Vector3D The color at the given point
             */
            const Math::Vector3D textureColorAt(const Math::Vector3D &point) const override;

            void builder(const libconfig::Setting &settings) override;

        private:
            // First texture to blend
            ITexture *_textureA;
            // Second texture to blend
            ITexture *_textureB;
    };
};

#endif /* !BLENDEDTEXTURE_HPP_ */
