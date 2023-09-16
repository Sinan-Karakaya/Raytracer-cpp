/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** MovingSphere
*/

#ifndef MOVINGSPHERE_HPP_
    #define MOVINGSPHERE_HPP_

    #include "PrimitiveList.hpp"
    #include "AMaterial.hpp"

namespace RayTracer::Geometry {
    class MovingSphere : public APrimitive {
        public:
            MovingSphere();
            ~MovingSphere();

            /**
             * @brief Check if a ray hits the sphere
             *
             * @param ray
             * @param t_min
             * @param t_max
             * @param rec
             * @return true
             * @return false
             */
            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;

            /**
             * @brief Get the Normal at a given point
             *
             * @param time0
             * @param time1
             * @param box
             * @return true
             * @return false
             */
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            void builder(const libconfig::Setting &settings) override;

        private:
            /**
             * @brief Get the Center object
             * Get the center of the sphere at a given time
             * @param time
             * @return Math::Vector3D The coordinates of the center at time
             */
            Math::Vector3D getCenter(double time) const;

        private:
            // The center of the sphere at time t0
            Math::Vector3D _center0;

            // The center of the sphere at time t1
            Math::Vector3D _center1;

            // The time at which the sphere is at _center0
            double _time0;
            // The time at which the sphere is at _center1
            double _time1;

            // The radius of the sphere
            double _radius;

            // The material of the sphere
            IMaterial *_material;
    };
};

#endif /* !MOVINGSPHERE_HPP_ */
