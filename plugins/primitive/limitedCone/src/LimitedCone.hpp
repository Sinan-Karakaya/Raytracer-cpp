/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** LimitedCone
*/

#ifndef LIMITEDCONE_HPP_
    #define LIMITEDCONE_HPP_

    #include "Quaternion.hpp"
    #include "APrimitive.hpp"
    #include "AMaterial.hpp"

namespace RayTracer::Geometry {
    //////////////////
    // Limited Cone //
    //////////////////
    class LimitedCone : public APrimitive {
        public:
            LimitedCone();
            ~LimitedCone();

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            bool capHit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const;
            bool IntersectsCap(const Ray &ray, const double &t, const double &cap_radius) const;

            void builder(const libconfig::Setting &settings) override;

        private:
            Math::Vector3D origin;
            double radius;
            double height;
            Math::Quaternion rotation;
            IMaterial *material;
    };
};

#endif /* !LIMITEDCONE_HPP_ */
