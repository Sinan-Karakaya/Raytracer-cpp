/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "PrimitiveList.hpp"
    #include "AMaterial.hpp"
    #include "Tools.hpp"
    #include "ONB.hpp"

namespace RayTracer::Geometry {
    class Sphere : public APrimitive {
        public:
            Sphere() : _origin(Math::Vector3D(0, 0, 0)), _radius(0), _material(new AMaterial()) {};
            Sphere(Math::Vector3D origin, double radius, IMaterial *material = new AMaterial());
            ~Sphere() override;

            /**
             * @brief Check if the ray hit the sphere
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
             * @brief Get the bounding box of the sphere
             *
             * @param time0
             * @param time1
             * @param box
             * @return true
             * @return false
             */
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            double pdfValue(const Math::Vector3D &origin, const Math::Vector3D &direction) const override;
            Math::Vector3D random(const Math::Vector3D &origin) const override;

            void builder(const libconfig::Setting &setting) override;

        private:
            /**
             * @brief Get the UV coordinates of the sphere
             *
             * @param point
             * @param u
             * @param v
             */
            static void getSphereUV(const Math::Vector3D &point, double &u, double &v);

        private:
            // The origin point of the sphere
            Math::Vector3D _origin;

            // The radius of the sphere
            double _radius;

            // The material of the sphere
            IMaterial *_material;
    };
};

#endif /* !SPHERE_HPP_ */
