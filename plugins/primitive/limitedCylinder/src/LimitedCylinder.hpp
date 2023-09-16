/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** LimitedCylinder
*/

#ifndef LIMITEDCYLINDER_HPP_
    #define LIMITEDCYLINDER_HPP_

    #include "APrimitive.hpp"
    #include "Quaternion.hpp"
    #include "AMaterial.hpp"

namespace RayTracer::Geometry {
    //////////////////////
    // Limited Cylinder //
    //////////////////////
    class LimitedCylinder : public APrimitive {
        public:
            LimitedCylinder();
            ~LimitedCylinder();

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            void builder(const libconfig::Setting &settings) override;
        private:
            Math::Vector3D center;
            double radius;
            double height;
            Math::Quaternion rotation;
            IMaterial *material;
            Math::AABB _box;
    };
};

#endif /* !LIMITEDCYLINDER_HPP_ */
