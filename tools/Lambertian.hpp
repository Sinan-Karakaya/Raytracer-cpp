/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Lambertian
*/

#ifndef LAMBERTIAN_HPP_
    #define LAMBETRIAN_HPP_

    #include "AMaterial.hpp"
    #include "SolidColor.hpp"
    #include "CosinePDF.hpp"

    #include <memory>

namespace RayTracer {
    class Lambertian : public AMaterial {
        public:
            Lambertian(const Math::Vector3D &albedo) : _albedo(new SolidColor(albedo)) {}
            Lambertian(ITexture *texture) : _albedo(texture) {}

            ~Lambertian()
            {
                if (_albedo)
                    delete _albedo;
            };

            /**
                * @brief This function is used to scatter the ray
                * In a Lambertian material, the ray is scattered depending on the angle between the ray and the normal
                * @param ray
                * @param rec
                * @param srec
                * @return true
                */
            bool scatter(const Ray &ray, const HitRecord &rec, ScatterRecord &srec) const override
            {
                (void)ray;

                srec.isSpecular = false;
                srec.attenuation = _albedo->colorAt(rec.point);
                srec.pdf = new CosinePDF(rec.normal);

                return true;
            }

            double scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const override
            {
                double cosine = rec.normal.dot(scattered.getDirection().unitVector());

                (void)ray;

                if (cosine < 0)
                    return 0;
                return cosine / M_PI;
            }

        private:
            ITexture *_albedo;
    };
};

#endif /* !LAMBERTIAN_HPP_ */
