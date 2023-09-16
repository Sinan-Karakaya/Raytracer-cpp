/*
** EPITECH PROJECT, 2023
** CosinePDF
** File description:
** CosinePDF
*/

#ifndef CosinePDF_HPP_
    #define CosinePDF_HPP_

    #include "IPDF.hpp"
    #include "ONB.hpp"
    #include "Tools.hpp"

namespace RayTracer {
    class CosinePDF : public IPDF {
        public:
            CosinePDF(const Math::Vector3D &w)
            {
                _uvw.buildFromW(w);
            }

            ~CosinePDF() override {};

            double value(const Math::Vector3D &direction) const override
            {
                double cosine = direction.unitVector().dot(_uvw.w());

                if (cosine <= 0)
                    return 0;
                return cosine / M_PI;
            }

            Math::Vector3D generate() const override
            {
                Tools toolBox;

                return _uvw.local(toolBox.randomCosineDirection());
            }

        private:
            ONB _uvw;
    };
};

#endif /* !CosinePDF_HPP_ */
