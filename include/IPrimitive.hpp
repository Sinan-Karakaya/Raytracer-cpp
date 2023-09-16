/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** IPrimitive
*/

#ifndef IPRIMITIVE_HPP_
    #define IPRIMITIVE_HPP_

    #include <libconfig.h++>

    #include "HitRecord.hpp"
    #include "AABB.hpp"
    #include "Lambertian.hpp"
    #include "LibLoader.hpp"
    #include "IMaterial.hpp"
    #include <unistd.h>
    #include "ITexture.hpp"

namespace RayTracer::Geometry {
    class IPrimitive
    {
    public:
        virtual ~IPrimitive() = default;

        /**
        * @brief Checks if a ray intersects with the object
        *
        * @param ray   : The ray to check
        * @param t_min : The minimum distance from the ray origin to the point of intersection
        * @param t_max : The maximum distance from the ray origin to the point of intersection
        * @param rec   : The HitRecord to fill if the ray intersects with the object
        * @return true
        * @return false
        */
        virtual bool hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const = 0;

        /**
        * @brief Calculates the bounding box of the object
        *
        * @param time0 : The start time of the object
        * @param time1 : The end time of the object
        * @param box  : The bounding box to fill
        * @return true
        * @return false
        */
        virtual bool bounding_box(double time0, double time1, Math::AABB &box) const = 0;

        virtual double pdfValue(const Math::Vector3D &origin, const Math::Vector3D &direction) const = 0;

        virtual Math::Vector3D random(const Math::Vector3D &origin) const = 0;

        virtual void builder(const libconfig::Setting &setting) = 0;

        virtual IMaterial *loadMaterial(const libconfig::Setting &setting) = 0;

        // virtual ITexture *loadTexture(const libconfig::Setting &setting) = 0;
    };
};

#endif /* !IPRIMITIVE_HPP_ */
