/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** AABB
*/

#ifndef AABB_HPP_
    #define AABB_HPP_

    #include "Vector3D.hpp"
    #include "Ray.hpp"

namespace Math {
    class AABB {
        public:
            // Ctor / Dtor
            AABB() : _min(Vector3D(0, 0, 0)), _max(Vector3D(0, 0, 0)) {};
            AABB(const Vector3D &a, const Vector3D &b) : _min(a), _max(b) {};
            ~AABB() {};

            // Getters
            Vector3D getMin() const
            {
                return _min;
            }

            Vector3D getMax() const
            {
                return _max;
            }

            /**
             * @brief Checks if a ray intersects with the AABB
             *
             * @param ray : the ray to check
             * @param t_min : the minimum distance
             * @param t_max : the maximum distance
             * @return true
             * @return false
             */
            bool hit(const RayTracer::Ray &ray, double t_min, double t_max) const
            {
                // invD represents the inverse of the ray's direction
                double invD = 0.0f;

                // t0 and t1 represent the minimum and maximum distance from the ray origin to the point of intersection
                double t0 = 0.0f;
                double t1 = 0.0f;

                // X, Y, Z
                for (int a = 0; a < 3; a++) {
                    invD = 1.0f / ray.getDirection()[a];
                    t0 = (getMin()[a] - ray.getOrigin()[a]) * invD;
                    t1 = (getMax()[a] - ray.getOrigin()[a]) * invD;

                    if (invD < 0.0f)
                        std::swap(t0, t1);

                    t_min = t0 > t_min ? t0 : t_min;
                    t_max = t1 < t_max ? t1 : t_max;

                    if (t_max <= t_min)
                        return false;
                }
                return true;
            }

            /**
             * @brief Calculates the bounding box of the object
             *
             * @param box1 : The bounding box to fill
             * @return AABB : The bounding box
             */
            AABB surrounding_box(const AABB &box1)
            {
                Vector3D small(fmin(getMin().x, box1.getMin().x),
                            fmin(getMin().y, box1.getMin().y),
                            fmin(getMin().z, box1.getMin().z));

                Vector3D big(fmax(getMax().x, box1.getMax().x),
                          fmax(getMax().y, box1.getMax().y),
                          fmax(getMax().z, box1.getMax().z));

                return AABB(small, big);
            }

        private:
            // The minimum point of the AABB
            Vector3D _min;

            // The maximum point of the AABB
            Vector3D _max;
    };
};

#endif /* !AABB_HPP_ */
