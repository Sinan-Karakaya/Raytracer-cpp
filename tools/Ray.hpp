/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Ray
*/

#ifndef RAY_HPP_
    #define RAY_HPP_

    #include "Matrix.hpp"
    #include "Quaternion.hpp"

namespace RayTracer {
    class Ray {
        public:
            /////////////////
            // Ctor & Dtor //
            /////////////////

            /**
             * @brief Construct a new Ray object
             *
             * @param origin The origin of the ray
             * @param direction The direction of the ray
             */
            Ray(Math::Vector3D origin = Math::Vector3D(0.0f, 0.0f, 0.0f), Math::Vector3D direction = Math::Vector3D(0.0f, 0.0f, 0.0f), double time = 0.0f) : _origin(origin), _direction(direction), _time(time) {};

            /**
             * @brief Destroy the Ray object
             *
             */
            ~Ray() {};

            //////////////
            // Operator //
            //////////////

            /**
             * @brief Compare two Ray between us
             *
             * @param ray
             * @return true
             * @return false
             */
            bool operator==(const Ray ray) const
            {
                return _origin == ray._origin && _direction == ray._direction;
            }

            ///////////////////////
            // Getters & Setters //
            ///////////////////////

            /**
             * @brief Get the origin point of the ray
             *
             * @return Math::Vector3D 
             */
            Math::Vector3D getOrigin() const
            {
                return _origin;
            };

            /**
             * @brief Get the direction of the ray
             *
             */
            Math::Vector3D getDirection() const
            {
                return _direction;
            }

            /**
             * @brief Get the position of the ray at a given distance
             *
             * @param t The distance from the ray origin
             * @return Math::Vector3D
             */
            Math::Vector3D getPoint(double t) const
            {
                return _origin + _direction * t;
            }

            /**
             * @brief Get the time of the ray
             *
             * @return double
             */
            double getTime() const
            {
                return _time;
            }

            /////////////
            // Methods //
            /////////////
            
            /**
             * @brief Transform the ray by a given matrix
             *
             * @param matrix The matrix to transform the ray
             * @return const Ray The transformed ray
             */
            const Ray transform(const Math::Matrix matrix) const
            {
                return Ray(matrix * _origin, matrix * _direction);
            }

            /**
             * @brief Transform the ray by a given quaternion
             *
             * @param quaternion 
             * @param point 
             * @return const Ray 
             */
            const Ray transformed(const Math::Quaternion quaternion, const Math::Vector3D &point) const
            {
                Math::Vector3D origin = quaternion.rotate(quaternion, (_origin - point));
                Math::Vector3D direction = quaternion.rotate(quaternion, _direction);

                return Ray(origin + point, direction);
            }

        private:
            Math::Vector3D _origin;
            Math::Vector3D _direction;
            double _time;
    };
};

#endif /* !RAY_HPP_ */
