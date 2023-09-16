/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** BVH
*/

#ifndef BVH_HPP_
    #define BVH_HPP_

    #include "PrimitiveList.hpp"
    #include "Tools.hpp"

    #include <vector>
    #include <algorithm>

namespace RayTracer::Geometry {
    class BVH : public APrimitive {
        public:
            BVH();
            BVH(const IPrimitive **list, int n, double time0, double time1);;
            BVH(const IPrimitive **list, int start, int end, double time0, double time1);

            ~BVH() override;

            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override;
            bool bounding_box(double time0, double time1, Math::AABB &box) const override;

            static bool box_compare(const IPrimitive *a, const IPrimitive *b, int axis);
            static bool box_x_compare(const IPrimitive *a, const IPrimitive *b);
            static bool box_y_compare(const IPrimitive *a, const IPrimitive *b);
            static bool box_z_compare(const IPrimitive *a, const IPrimitive *b);

        private:
            IPrimitive *_left;
            IPrimitive *_right;
            Math::AABB _box;
    };
};

#endif /* !BVH_HPP_ */
