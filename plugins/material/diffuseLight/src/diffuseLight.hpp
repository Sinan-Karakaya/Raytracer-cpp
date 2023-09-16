/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** diffuseLight
*/

#ifndef DIFFUSELIGHT_HPP_
    #define DIFFUSELIGHT_HPP_

    #include "AMaterial.hpp"
    #include "ITexture.hpp"

    #include <memory>

namespace RayTracer::Plugin {
    class diffuseLight : public AMaterial {
        public:
            diffuseLight(ITexture *texture = nullptr);
            diffuseLight(const Math::Vector3D &color = Math::Vector3D(0.0, 0.0, 0.0));

            ~diffuseLight() override;

            /**
            * @brief This function is used to scatter the ray
            * But in a diffuseLight material, the ray is not scattered, so it's always false
            * @param ray         // unused
            * @param rec         // unused
            * @param attenuation // unused
            * @param scattered   // unused
            * @return false
            */
            bool scatter(const Ray &ray, const HitRecord &rec, ScatterRecord &srec) const override
            {
                (void)ray;
                (void)rec;
                (void)srec;
                return false;
            };

            /**
            * @brief This function is used to get the color of the light
            *
            * @param u
            * @param v
            * @param point
            * @return Math::Vector3D The color of the light
            */
            Math::Vector3D emitted(const Ray &ray, const HitRecord &rec, double u, double v, const Math::Vector3D &point) const override
            {
                (void)ray;
                (void)u;
                (void)v;

                if (rec.frontFace == true)
                    return _emit->colorAt(point);
                return Math::Vector3D(1.0, 1.0, 1.0);
            };

            void init(const libconfig::Setting &setting) override;

        private:
            // The color of the light
            ITexture *_emit;
    };
};

#endif /* !DIFFUSELIGHT_HPP_ */
