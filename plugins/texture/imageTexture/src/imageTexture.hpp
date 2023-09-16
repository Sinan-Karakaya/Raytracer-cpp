/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** imageTexture
*/

#ifndef IMAGETEXTURE_HPP_
    #define IMAGETEXTURE_HPP_

    #define STB_IMAGE_IMPLEMENTATION
        #include <stb_image.h>

    #include "ATexture.hpp"

namespace RayTracer {
    class ImageTexture : public ATexture {
        public:
            /**
             * @brief Default Constructor for Init the ImageTexture
             *
             */
            ImageTexture();

            ~ImageTexture();

            /**
             * @brief This function is used to get the color of a imageTexture at a specific point
             *
             * @param u
             * @param v
             * @param p
             * @return Math::Vector3D
             */
            const Math::Vector3D textureColorAt(const Math::Vector3D &point) const override;

            void builder(const libconfig::Setting &settings) override;

        // DEFINE value for imageTexture
        private:
            // The number of bytes used to represent a color pixel
            static const int BYTES_PER_PIXEL = 3;

        private:
            // The image data
            unsigned char *_data;

            // The image width and height
            int _width;
            int _height;

            // The number of bytes used to store one image row
            int _bytes_per_scanline;
    };
};

#endif /* !IMAGETEXTURE_HPP_ */
