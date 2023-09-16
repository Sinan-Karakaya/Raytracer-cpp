/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** ATexture
*/

#ifndef ATEXTURE_HPP_
    #define ATEXTURE_HPP_

    #include "ITexture.hpp"

namespace RayTracer {
    class ATexture : public ITexture {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new ATexture object
             * with a default texture matrix initialized to the identity matrix
             */
            ATexture() : _textureMatrix(Math::Matrix(1, 1))
            {
                _textureMatrix = _textureMatrix.identityMatrix(4);
            }

            virtual ~ATexture() override {};

            //////////////////////
            // Getter & Setters //
            //////////////////////

            /**
             * @brief Get the Texture Matrix object
             * The Matrix represent the transformation to apply to the texture
             * @return Math::Matrix The texture matrix
             */
            Math::Matrix getTextureMatrix() const override
            {
                return _textureMatrix;
            }

            /**
             * @brief Set the Texture Matrix object
             * The Matrix represent the transformation to apply to the texture
             * @param Matrix The texture matrix
             */
            void setTextureMatrix(const Math::Matrix Matrix) override
            {
                _textureMatrix = Matrix;
            }

            /////////////
            // Methods //
            /////////////

            /**
             * @brief Get the color at the given point
             *
             * @param point The point to get the color from
             * @return const Math::Vector3D The color at the given point
             */
            const Math::Vector3D colorAt(const Math::Vector3D &point) const override
            {
                Math::Vector3D texturePoint = _textureMatrix.inverse() * point;

                return textureColorAt(texturePoint);
            }

            virtual const Math::Vector3D textureColorAt(const Math::Vector3D &point) const = 0;

            /**
             * @brief Create a new texture from the given setting
             *
             * @param setting The setting to create the texture from
             * @return ITexture* The created texture
             */
            virtual void builder(const libconfig::Setting &setting) = 0;

        private:
            // The texture matrix
            Math::Matrix _textureMatrix;
    };
};

#endif /* !ATEXTURE_HPP_ */
