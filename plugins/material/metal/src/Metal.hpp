/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** METAL
*/

#ifndef METAL_HPP_
    #define METAL_HPP_

    #include "AMaterial.hpp"
    #include "Tools.hpp"

namespace RayTracer::Plugin {
    class Metal : public AMaterial {
        public:
            Metal(const Math::Vector3D &albedo = Math::Vector3D(0.0, 0.0, 0.0), double fuzz = 0.0);
            ~Metal() override = default;

            /**
            * @brief This function is used to scatter the ray
            * In a Metal material, the ray is scattered depending on the angle between the ray and the normal
            * @param ray
            * @param rec
            * @param srec
            * @return true
            * @return false
            */
            bool scatter(const Ray &ray, const HitRecord &rec, ScatterRecord &srec) const override
            {
                Math::Vector3D reflected = ray.getDirection().unitVector().reflect(rec.normal);
                Tools toolBox;

                srec.specularRay = Ray(rec.point, reflected + toolBox.randomInUnitSphere() * _fuzz);
                srec.attenuation = _albedo;
                srec.isSpecular = true;
                srec.pdf = nullptr;
                return true;
            }

            void init(const libconfig::Setting &setting) override;

        private:
            double _fuzz;
            Math::Vector3D _albedo;
    };
};

#endif /* !METAL_HPP_ */
