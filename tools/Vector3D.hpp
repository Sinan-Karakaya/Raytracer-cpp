/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Vector3D
*/

#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <iostream>
    #include <cmath>

namespace Math {
    class Vector3D {
        public:
            // Ctor / Dtor
            Vector3D(double x = 0.0f, double y = 0.0f, double z = 0.0f, double w = 0.0f) : x(x), y(y), z(z), w(w) {};
            Vector3D(const Vector3D &other) : x(other.x), y(other.y), z(other.z), w(other.w) {};
            ~Vector3D() = default;

            // Operators
            Vector3D operator+(const Vector3D &other) const
            {
                return Vector3D(x + other.x, y + other.y, z + other.z);
            };

            Vector3D operator-(const Vector3D &other) const
            {
                return Vector3D(x - other.x, y - other.y, z - other.z);
            };

            Vector3D operator*(const Vector3D &other) const
            {
                return Vector3D(x * other.x, y * other.y, z * other.z);
            };

            Vector3D operator*(const double &other) const
            {
                return Vector3D(x * other, y * other, z * other);
            };


            Vector3D operator/(const Vector3D &other) const
            {
                return Vector3D(x / other.x, y / other.y, z / other.z);
            };

            Vector3D operator/(const double &other) const
            {
                return Vector3D(x / other, y / other, z / other);
            };

            Vector3D operator%(const Vector3D &other) const
            {
                return Vector3D(y * other.z - z * other.y, z *
                    other.x - x * other.z, x * other.y - y * other.x);
            };

            Vector3D operator-() const
            {
                return Vector3D(-x, -y, -z);
            };

            Vector3D operator+=(const Vector3D &other)
            {
                x += other.x;
                y += other.y;
                z += other.z;
                return *this;
            };

            Vector3D operator-=(const Vector3D &other)
            {
                x -= other.x;
                y -= other.y;
                z -= other.z;
                return *this;
            };

            Vector3D operator*=(const Vector3D &other)
            {
                x *= other.x;
                y *= other.y;
                z *= other.z;
                return *this;
            };

            Vector3D operator/=(const Vector3D &other)
            {
                x /= other.x;
                y /= other.y;
                z /= other.z;
                return *this;
            };

            Vector3D operator/=(const double &other)
            {
                x /= other;
                y /= other;
                z /= other;
                return *this;
            };

            Vector3D operator%=(const Vector3D &other)
            {
                x = y * other.z - z * other.y;
                y = z * other.x - x * other.z;
                z = x * other.y - y * other.x;
                return *this;
            };

            Vector3D &operator=(const Vector3D &other) = default;

            double &operator[](int index)
            {
                if (index == 0)
                    return x;
                if (index == 1)
                    return y;
                return z;
            }

            // Comparators
            bool operator==(const Vector3D &other) const
            {
                return (x == other.x && y == other.y && z == other.z);
            };

            bool operator!=(const Vector3D &other) const
            {
                return (x != other.x || y != other.y || z != other.z);
            };

            bool operator<(const Vector3D &other) const
            {
                return (x < other.x && y < other.y && z < other.z);
            };

            bool operator>(const Vector3D &other) const
            {
                return (x > other.x && y > other.y && z > other.z);
            };

            bool operator<=(const Vector3D &other) const
            {
                return (x <= other.x && y <= other.y && z <= other.z);
            };

            bool operator>=(const Vector3D &other) const
            {
                return (x >= other.x && y >= other.y && z >= other.z);
            };

            bool near_zero() const
            {
                const auto s = 1e-8;

                return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
            }

            // Methods

            /**
                * @brief Get the length of the vector
                *
                * @return double length
                */
            double length() const
            {
                return sqrt(x * x + y * y + z * z + w + w);
            };

            /**
                * @brief Get the squared length of the vector
                *
                * @return double squared length
                */
            double lengthSquared() const
            {
                return x * x + y * y + z * z + w + w;
            };

            /**
                * @brief Get the dot product of the vector
                *
                * @param other
                * @return double dot product
                */
            double dot(const Vector3D &other) const
            {
                return x * other.x + y * other.y + z * other.z;
            };

            /**
                * @brief Get the unit vector of the vector
                *
                * @return Vector3D unit vector
                */
            Vector3D unitVector() const
            {
                return *this / length();
            };

            /**
                * @brief Get the reflected vector
                *
                * @param normal
                * @return Vector3D reflected vector
                */
            Vector3D reflect(const Vector3D &normal) const
            {
                return *this - normal * (this->dot(normal) * 2.0f);
            }

            /**
                * @brief Get the refracted vector
                *
                * @param normal
                * @param etai_over_etat
                * @param refracted
                * @return true
                * @return false
                */
            bool refract(const Vector3D &normal, double etai_over_etat, Vector3D &refracted) const
            {
                Vector3D uv = this->unitVector();

                double dt = uv.dot(normal);
                double discriminant = 1.0f - etai_over_etat * etai_over_etat * (1.0f - dt * dt);

                if (discriminant > 0) {
                    refracted = (uv - normal * dt) * etai_over_etat - normal * sqrt(discriminant);
                    return true;
                }

                return false;
            }

            /**
                * @brief Get the cross product of the vector
                *
                * @param other
                * @return Vector3D cross product
                */
            Vector3D cross(const Vector3D &other) const
            {
                return Vector3D(this->y * other.z - this->z * other.y,
                            this->z * other.x - this->x * other.z,
                            this->x * other.y - this->y * other.x);
            }

            /**
                * @brief Normalize the vector
                *
                */
            Vector3D normalize()
            {
                double len = length();

                x /= len;
                y /= len;
                z /= len;
                return *this;
            };

            /**
             * @brief Get the blended vector
             *
             * @param other
             * @return Vector3D
             */
            Vector3D blend(const Vector3D &other) const
            {
                return Vector3D(
                    (this->x + other.x) / 2.0,
                    (this->y + other.y) / 2.0,
                    (this->z + other.z) / 2.0
                );
            }

            double x;
            double y;
            double z;
            double w;
    };
};

#endif /* !VECTOR3D_HPP_ */
