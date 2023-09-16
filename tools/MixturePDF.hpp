/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** MixturePDF
*/

#ifndef MIXTUREPDF_HPP_
    #define MIXTUREPDF_HPP_

    #include "IPDF.hpp"

    #include <memory>

namespace RayTracer {
    class MixturePDF : public IPDF {
        public:
            MixturePDF(IPDF *pdf0, IPDF *pdf1)
            {
                _pdf[0] = pdf0;
                _pdf[1] = pdf1;
            }

            ~MixturePDF() {};

            double value(const Math::Vector3D &direction) const override
            {
                return 0.5 * _pdf[0]->value(direction) + 0.5 * _pdf[1]->value(direction);
            }

            Math::Vector3D generate() const override
            {
                if (drand48() < 0.5)
                    return _pdf[0]->generate();
                return _pdf[1]->generate();
            }

        private:
            IPDF *_pdf[2];
    };
};

#endif /* !MIXTUREPDF_HPP_ */
