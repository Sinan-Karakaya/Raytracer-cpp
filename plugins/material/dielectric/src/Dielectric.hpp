/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** DIELECTRIC
*/

#ifndef DIELECTRIC_HPP_
    #define DIELECTRIC_HPP_

    #include "AMaterial.hpp"

namespace RayTracer::Plugin {
    class Dielectric : public AMaterial {
        public:
            Dielectric(double ref_idx = 0.0);
            ~Dielectric() override;

            /**
             * @brief This function is used to scatter the ray
             * In a Dielectric material, the ray is scattered depending on the angle between the ray and the normal
             * @param ray
             * @param rec
             * @param srec
             * @return true
             * @return false
             */
            bool scatter(const Ray &ray, const HitRecord &rec, ScatterRecord &srec) const override
            {
                double refraction_ratio = rec.frontFace ? (1.0f / _ref_idx) : _ref_idx;

                Math::Vector3D unit_direction = ray.getDirection().unitVector();

                double cos_theta = fmin(rec.normal.dot(-unit_direction), 1.0f);
                double sin_theta = sqrt(1.0f - cos_theta * cos_theta);

                bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
                Math::Vector3D direction;

                srec.isSpecular = true;
                srec.pdf = nullptr;
                srec.attenuation = Math::Vector3D(1.0f, 1.0f, 1.0f);

                if (cannot_refract || schlick(cos_theta, refraction_ratio) > drand48())
                    direction = unit_direction.reflect(rec.normal);
                else
                    unit_direction.refract(rec.normal, refraction_ratio, direction);

                srec.specularRay = Ray(rec.point, direction, ray.getTime());
                return true;
            }

            void init(const libconfig::Setting &setting);

        private:
            /**
             * @brief This function is used to calculate the schlick approximation
             *
             * @param cosine  // The cosine of the angle between the ray and the normal
             * @param ref_idx // The refraction index
             * @return double // The schlick approximation
             */
            double schlick(double cosine, double ref_idx) const;

        private:
            double _ref_idx;
    };
};

#endif /* !DIELECTRIC_HPP_ */
