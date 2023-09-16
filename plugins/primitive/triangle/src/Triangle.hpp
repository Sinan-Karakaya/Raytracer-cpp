/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
    #define TRIANGLE_HPP_

    #include "APrimitive.hpp"

namespace RayTracer::Geometry {
    class Triangle : public APrimitive {
        public:
            Triangle(Math::Vector3D pa, Math::Vector3D pb, Math::Vector3D pc, IMaterial *material);
            ~Triangle();

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double t0, double t1, Math::AABB &box) const override;

            void builder(const libconfig::Setting &setting) override;

        private:
            Math::Vector3D _pa;
            Math::Vector3D _pb;
            Math::Vector3D _pc;
            IMaterial *_material;
    };
};

#endif /* !TRIANGLE_HPP_ */
