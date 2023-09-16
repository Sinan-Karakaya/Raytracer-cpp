/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** IPDF
*/

#ifndef IPDF_HPP_
    #define IPDF_HPP_

    #include "Vector3D.hpp"

namespace RayTracer {
    class IPDF {
        public:
            virtual ~IPDF() = default;

            virtual double value(const Math::Vector3D &direction) const = 0;
            virtual Math::Vector3D generate() const = 0;
    };
};

#endif /* !IPDF_HPP_ */
