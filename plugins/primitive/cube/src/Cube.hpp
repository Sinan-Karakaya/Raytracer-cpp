/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Cube
*/

#ifndef CUBE_HPP_
    #define CUBE_HPP_

    #include "Rectangle.hpp"
    #include "PrimitiveList.hpp"
    #include "AMaterial.hpp"

namespace RayTracer::Geometry {
    class Cube : public APrimitive {
        public:
            Cube();
            ~Cube();

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;
            void builder(const libconfig::Setting &settings) override;
        private:
            // The min point of the cube
            Math::Vector3D _minBox;

            // The max point of the cube
            Math::Vector3D _maxBox;

            // The sides of the cube (RectanglePrimitive)
            IPrimitive *_sides;

        // DEFINE value for Cube
        private:
            // The number of sides of a cube.
            const int CUBESIDES = 6;
    };
};

#endif /* !CUBE_HPP_ */
