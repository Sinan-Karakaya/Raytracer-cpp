/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Plane
*/

#ifndef PLANE_HPP_
    #define PLANE_HPP_

    #include "APrimitive.hpp"
    #include "AMaterial.hpp"

    #include <string>

namespace RayTracer::Geometry {
    class Plane : public APrimitive {
        public:
            Plane() : _normal(Math::Vector3D(0, 0, 0)), _position(0), _material(nullptr) {};
            Plane(const std::string &axis, double position, IMaterial *material = new AMaterial());

            ~Plane() override;

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            void builder(const libconfig::Setting &setting) override;

        private:
            Math::Vector3D _normal;
            double _position;
            IMaterial *_material;
    };
};

#endif /* !PLANE_HPP_ */
