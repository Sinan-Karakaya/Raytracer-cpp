/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** HitRecord
*/

#ifndef HITRECORD_HPP_
    #define HITRECORD_HPP_

    #include "Vector3D.hpp"
    #include "Ray.hpp"

    #include <memory>

namespace RayTracer {
    class IMaterial;
    class HitRecord {
        public:
            /**
             * @brief A structure containing information about the intersection between a ray and an object
             * Vector3D point : The point of intersection
             * Vector3D normal : the normal at the point of intersection
             * std::shared_ptr<IMaterial> material : The material of the object
             * bool frontFace : true if the ray is hitting the front face of the object, false otherwise
             * double t : The distance from the ray origin to the point of intersection
             * double u : The u coordinate of the point of intersection
             * double v : The v coordinate of the point of intersection
             */
            HitRecord() = default;
            ~HitRecord() = default;

            Math::Vector3D point;
            Math::Vector3D normal;
            IMaterial *material;
            bool frontFace;
            double t;
            double u;
            double v;

            void setFaceNormal(const RayTracer::Ray &ray, const Math::Vector3D &outcome_normal)
            {
                if (ray.getDirection().dot(outcome_normal) < 0)
                    frontFace = true;
                else
                    frontFace = false;

                if (frontFace)
                    normal = outcome_normal;
                else
                    normal = -outcome_normal;
            }
    };
};

#endif /* !HITRECORD_HPP_ */
