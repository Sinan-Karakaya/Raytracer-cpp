/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** PrimitivePDF
*/

#ifndef PRIMITIVEPDF_HPP_
    #define PRIMITIVEPDF_HPP_

    #include "IPDF.hpp"
    #include "IPrimitive.hpp"

namespace RayTracer {
    class PrimitivePDF : public IPDF {
        public:
            PrimitivePDF(Geometry::IPrimitive *object, const Math::Vector3D &origin) : _object(object), _origin(origin) {};
            PrimitivePDF(const PrimitivePDF &other) = default;
            PrimitivePDF() = default;
            ~PrimitivePDF() override {};

            double value(const Math::Vector3D &direction) const override
            {
                if (_object == nullptr)
                    return 0.0f;
                return _object->pdfValue(_origin, direction);
            }

            Math::Vector3D generate() const override
            {
                if (_object == nullptr)
                    return Math::Vector3D(1.0f, 0.0f, 0.0f);
                return _object->random(_origin);
            }

        private:
            Geometry::IPrimitive *_object;
            Math::Vector3D _origin;
    };
};

#endif /* !PRIMITIVEPDF_HPP_ */
