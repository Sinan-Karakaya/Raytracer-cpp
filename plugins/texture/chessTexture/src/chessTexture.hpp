/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** chessTexture
*/

#ifndef CHESSTEXTURE_HPP_
    #define CHESSTEXTURE_HPP_

    #include "SolidColor.hpp"

namespace RayTracer {
class ChessTexture : public ATexture {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new Chess Texture object
             * Create a grid texture with two colors
             * @param colorA The color of the first square
             * @param colorB The color of the second square
             */
            ChessTexture();

            /**
             * @brief Destroy the Chess Texture object
             *
             */
            ~ChessTexture() override;

            ///////////////////////
            // Setters & Getters //
            ///////////////////////

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
            // The first color of the chess texture
            ITexture *_colorA;
            // The second color of the chess texture
            ITexture *_colorB;
    };
};

#endif /* !CHESSTEXTURE_HPP_ */
