/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** ScatterRecord
*/

#ifndef SCATTERRECORD_HPP_
    #define SCATTERRECORD_HPP_

    #include "IPDF.hpp"
    #include "Ray.hpp"

    #include <memory>

namespace RayTracer {
    class ScatterRecord {
        public:
            ScatterRecord() = default;
            ~ScatterRecord() = default;

            Ray specularRay;
            bool isSpecular;
            Math::Vector3D attenuation;
            IPDF *pdf;
    };
};

#endif /* !SCATTERRECORD_HPP_ */
