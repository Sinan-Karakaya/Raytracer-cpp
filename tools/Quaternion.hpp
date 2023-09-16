/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Quaternion
*/

#ifndef QUATERNION_HPP_
    #define QUATERNION_HPP_

    #include "Vector3D.hpp"

namespace Math {
    class Quaternion {
        public:
            Quaternion() : _w(1), _v(0, 0, 0) {};
            Quaternion(double w, double x, double y, double z) : _w(w), _v(x, y, z) {};
            Quaternion(double w, const Vector3D &v) : _w(w), _v(v) {};
            Quaternion(const Quaternion &other) : _w(other._w), _v(other._v) {};
            ~Quaternion() {};

            double norm() const
            {
                return sqrt(_w * _w + _v.lengthSquared());
            }

            Quaternion normalized() const
            {
                double n = norm();

                return Quaternion(_w / n, _v / n);
            }

            Quaternion conjugate() const
            {
                return Quaternion(_w, -_v);
            }

            Quaternion operator*(const Quaternion &q) const
            {
                return Quaternion(_w * q._w - _v.dot(q._v), q._v * _w + _v * q._w + _v.cross(q._v));
            }

            Quaternion operator=(const Quaternion &q)
            {
                _w = q._w;
                _v = q._v;

                return *this;
            }

            Quaternion inverse() const
            {
                Quaternion q(*this);

                return q.conjugate() / q.norm();
            }

            Quaternion operator/(double scalar) const
            {
                return Quaternion(_w / scalar, _v / scalar);
            }

            Vector3D rotate(const Quaternion &q, const Vector3D &v) const
            {
                Quaternion p(0, Math::Vector3D(v.x, v.y, v.z));
                Quaternion q_inv = q.inverse();
                Quaternion result = q * p * q_inv;

                return result._v;
            }

            Quaternion from_axis_angle(Vector3D &axis, double angle)
            {
                double s = std::sin(angle / 2);
                double c = std::cos(angle / 2);

                return Quaternion(c, axis.normalize() * s);
            }

            double _w;
            Vector3D _v;
    };
};

#endif /* !QUATERNION_HPP_ */
