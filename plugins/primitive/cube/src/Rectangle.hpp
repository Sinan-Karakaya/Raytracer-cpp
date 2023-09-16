/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Rectangle
*/

#ifndef RECTANGLE_HPP_
    #define RECTANGLE_HPP_

    #include "PrimitiveList.hpp"
    #include "Tools.hpp"
    #include "AMaterial.hpp"

namespace RayTracer::Geometry {
    class XYRectangle : public APrimitive {
        public:
            XYRectangle(double p0, double p1, double p2, double p3, double k, IMaterial *material = new AMaterial());
            ~XYRectangle() override;

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &output_box) const override;
            void builder(const libconfig::Setting &setting) override;
        private:
            double x0;
            double x1;
            double y0;
            double y1;
            double k;
            IMaterial *material;
    };

    class XZRectangle : public APrimitive {
        public:
            XZRectangle(double p0, double p1, double p2, double p3, double k, IMaterial *material = new AMaterial());
            ~XZRectangle() override;

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &output_box) const override;
            double pdfValue(const Math::Vector3D& origin, const Math::Vector3D& v) const override;
            Math::Vector3D random(const Math::Vector3D& origin) const override;

            void builder(const libconfig::Setting &setting) override;
        private:
            double x0;
            double x1;
            double z0;
            double z1;
            double k;
            IMaterial *material;
    };

    class YZRectangle : public APrimitive {
        public:
            YZRectangle(double p0, double p1, double p2, double p3, double k, IMaterial *material = new AMaterial());
            ~YZRectangle() override;

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &output_box) const override;

            void builder(const libconfig::Setting &setting) override;
        private:
            double y0;
            double y1;
            double z0;
            double z1;
            double k;
            IMaterial *material;
    };
};

#endif /* !RECTANGLE_HPP_ */
