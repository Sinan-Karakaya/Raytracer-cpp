/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** IMaterial
*/

#ifndef IMATERIAL_HPP_
    #define IMATERIAL_HPP_

    #include "HitRecord.hpp"
    #include "ScatterRecord.hpp"
    #include "Ray.hpp"
    #include "libconfig.h++"

namespace RayTracer {
    class IMaterial {
        public:
            virtual ~IMaterial() = default;

            virtual bool scatter(const Ray &ray, const HitRecord &rec, ScatterRecord &srec) const = 0;
            virtual Math::Vector3D emitted(const Ray &ray, const HitRecord &rec, double u, double v, const Math::Vector3D &point) const = 0;
            virtual double scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const = 0;

            virtual void init(const libconfig::Setting &setting) = 0;

            template<typename T, typename... Args>
            static IMaterial *factory(Args &&... args)
            {
                return new T(std::forward<Args>(args)...);
            }
    };
};

#endif /* !IMATERIAL_HPP_ */
