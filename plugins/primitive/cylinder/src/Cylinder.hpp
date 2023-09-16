/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Cylinder
*/

#ifndef CYLINDER_HPP_
    #define CYLINDER_HPP_

    #include "APrimitive.hpp"
    #include "Quaternion.hpp"
    #include "AMaterial.hpp"

namespace RayTracer::Geometry {
    ///////////////////////
    // Infinite Cylinder //
    ///////////////////////
    class Cylinder : public APrimitive {
        public:
            Cylinder();
            ~Cylinder();

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            void builder(const libconfig::Setting &setting) override;

        private:
            Math::Vector3D center;
            double radius;
            Math::Quaternion rotation;
            IMaterial *material;
            Math::AABB _box;
    };
};

#endif /* !CYLINDER_HPP_ */
