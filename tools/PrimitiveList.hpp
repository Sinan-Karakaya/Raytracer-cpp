/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** PrimitiveList
*/

#ifndef PRIMITIVELIST_HPP_
    #define PRIMITIVELIST_HPP_

    #include "APrimitive.hpp"
    #include "Tools.hpp"

    #include <vector>

namespace RayTracer::Geometry {
    class PrimitiveList : public APrimitive {
        public:
            // Constructor & Destructor
            PrimitiveList(const PrimitiveList &other) = default;
            PrimitiveList(IPrimitive **list = nullptr, size_t size = 0) : _primitives(list, list + size) {};

            ~PrimitiveList() override {
                for (auto &primitive : _primitives)
                    delete primitive;
            }

            /**
            * @brief Loop on all primitives and check if the ray intersects with one of them
            *
            * @param ray
            * @param t_min
            * @param t_max
            * @param rec
            * @return true
            * @return false
            */
            bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const override
            {
                HitRecord temp_rec;
                bool hit_anything = false;
                double closest_so_far = t_max;

                for (auto &primitive : _primitives) {
                    if (primitive->hit(ray, t_min, closest_so_far, temp_rec)) {
                        hit_anything = true;
                        closest_so_far = temp_rec.t;
                        rec = temp_rec;
                    }
                }
                return hit_anything;
            }

            /**
            * @brief Get the bounding box of the primitive list
            *
            * @param time0
            * @param time1
            * @param box
            * @return true
            * @return false
            */
            bool bounding_box(double time0, double time1, Math::AABB &box) const override
            {
                Math::AABB temp_box;

                if (_primitives.empty())
                    return false;
                if (!_primitives[0]->bounding_box(time0, time1, temp_box))
                    return false;
                else
                    box = temp_box;
                for (auto &primitive : _primitives) {
                    if (!primitive->bounding_box(time0, time1, temp_box))
                        return false;
                    box = box.surrounding_box(temp_box);
                }
                return true;
            }

            double pdfValue(const Math::Vector3D &origin, const Math::Vector3D &direction) const override
            {
                double weight = 1.0 / _primitives.size();
                double sum = 0.0f;

                for (auto &primitive : _primitives)
                    sum += weight * primitive->pdfValue(origin, direction);
                return sum;
            }

            Math::Vector3D random(const Math::Vector3D &origin) const override
            {
                Tools toolBox;

                return _primitives[toolBox.random_int(0, _primitives.size() - 1)]->random(origin);
            }

            void builder(const libconfig::Setting &setting) override
            {
                (void)setting;
                return;
            }

            // The list of primitives
            std::vector<IPrimitive *> _primitives;
    };
};

#endif /* !PRIMITIVELIST_HPP_ */
