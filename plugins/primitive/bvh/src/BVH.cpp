/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** BVH
*/

#include "BVH.hpp"

namespace RayTracer::Geometry {
    BVH::BVH() {};
    BVH::BVH(const IPrimitive **list, int n, double time0, double time1) : BVH(list, 0, n, time0, time1) {};
    BVH::BVH(const IPrimitive **list, int start, int end, double time0, double time1)
    {
        std::vector<const IPrimitive *> primitives(list, list + end - start);

        int axis = Math::random_int(0, 2);
        size_t object_span = end - start;
        auto comparator = (axis == 0) ? &BVH::box_x_compare : ((axis == 1) ? &BVH::box_y_compare : &BVH::box_z_compare);

        if (object_span == 1) {
            _left = _right = const_cast<IPrimitive *>(primitives[0]);
        } else if (object_span == 2) {
            if (comparator(const_cast<IPrimitive *>(primitives[0]), const_cast<IPrimitive *>(primitives[1]))) {
                _left = const_cast<IPrimitive *>(primitives[0]);
                _right = const_cast<IPrimitive *>(primitives[1]);
            } else {
                _left = const_cast<IPrimitive *>(primitives[1]);
                _right = const_cast<IPrimitive *>(primitives[0]);
            }
        } else {
            std::sort(primitives.begin(), primitives.end(), comparator);

            int mid = start + object_span / 2;

            _left = new BVH(primitives.data(), start, mid, time0, time1);
            _right = new BVH(primitives.data(), mid, end, time0, time1);
        }

        Math::AABB box_left;
        Math::AABB box_right;

        if (!_left->bounding_box(time0, time1, box_left) || !_right->bounding_box(time0, time1, box_right))
            throw std::runtime_error("No bounding box in BVH constructor.");
        _box = box_left.surrounding_box(box_right);
    }

    BVH::~BVH()
    {
        /*if (_left)
            delete left;
        if (_right)
            delete right;*/
    }

    bool BVH::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override
    {
        if (!_box.hit(ray, t_min, t_max))
            return false;

        bool hit_left = _left->hit(ray, t_min, t_max, rec);
        bool hit_right = _right->hit(ray, t_min, hit_left ? rec.t : t_max, rec);

        return hit_left || hit_right;
        return true;
    }

    bool BVH::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        (void)(time0);
        (void)(time1);

        box = _box;
        return true;
    }

    ////////////////////
    // Box Comparator //
    ////////////////////
    bool BVH::box_compare(const IPrimitive *a, const IPrimitive *b, int axis)
    {
        Math::AABB box_a;
        Math::AABB box_b;

        if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
            throw std::runtime_error("No bounding box in BVH constructor.");
        return box_a.getMin()[axis] < box_b.getMax()[axis];
    }

    bool BVH::box_x_compare(const IPrimitive *a, const IPrimitive *b)
    {
        return box_compare(a, b, 0);
    }

    bool BVH::box_y_compare(const IPrimitive *a, const IPrimitive *b)
    {
        return box_compare(a, b, 1);
    }

    bool BVH::box_z_compare(const IPrimitive *a, const IPrimitive *b)
    {
        return box_compare(a, b, 2);
    }
};
