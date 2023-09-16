/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Cone
*/

#ifndef CONE_HPP_
    #define CONE_HPP_

    #include "Quaternion.hpp"
    #include "APrimitive.hpp"
    #include "AMaterial.hpp"

namespace RayTracer::Geometry {
    ///////////////////
    // Infinite Cone //
    ///////////////////
    class Cone : public APrimitive {
        public:
            Cone();
            ~Cone();

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            void builder(const libconfig::Setting &settings) override;

        private:
            Math::Vector3D origin;
            double radius;
            Math::Quaternion rotation;
            IMaterial *material;
    };
};

#endif /* !CONE_HPP_ */
