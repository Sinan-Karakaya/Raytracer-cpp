/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** ONB
*/

#ifndef ONB_HPP_
    #define ONB_HPP_

    #include "Vector3D.hpp"

namespace RayTracer {
    class ONB {
        public:
            ONB() {};
            ~ONB() {};

            Math::Vector3D operator[](int i) const
            {
                return axis[i];
            }

            Math::Vector3D u() const
            {
                return axis[0];
            }

            Math::Vector3D v() const
            {
                return axis[1];
            }

            Math::Vector3D w() const
            {
                return axis[2];
            }

            Math::Vector3D local(double a, double b, double c) const
            {
                return u() * a + v() * b + w() * c;
            }

            Math::Vector3D local(const Math::Vector3D &a) const
            {
                return u() * a.x + v() * a.y + w() * a.z;
            }

            void buildFromW(const Math::Vector3D &normal)
            {
                axis[2] = normal.unitVector();

                Math::Vector3D a = (fabs(w().x) > 0.9f) ? Math::Vector3D(0.0f, 1.0f, 0.0f) : Math::Vector3D(1.0f, 0.0f, 0.0f);

                axis[1] = (w().cross(a)).unitVector();
                axis[0] = w().cross(v());
            }

        private:
            Math::Vector3D axis[3];
    };
};

#endif /* !ONB_HPP_ */
