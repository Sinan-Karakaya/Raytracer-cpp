/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** AMaterial
*/

#ifndef AMATERIAL_HPP_
    #define AMATERIAL_HPP_

    #include "IMaterial.hpp"

namespace RayTracer {
    class AMaterial : public IMaterial {
        public:
            virtual ~AMaterial() override = default;
            virtual bool scatter(const Ray &ray, const HitRecord &rec, ScatterRecord &srec) const
            {
                (void)ray;
                (void)rec;
                (void)srec;

                return false;
            }

            /**
                * @brief This function is used to emit light from a material
                * A AMaterial can't emit light, so it returns a black vector
                * @param u (unused)
                * @param v (unused)
                * @param p (unused)
                * @return const Math::Vector3D(0, 0, 0) // Black vector
                */
            virtual Math::Vector3D emitted(const Ray &ray, const HitRecord &rec, double u, double v, const Math::Vector3D &point) const
            {
                (void)ray;
                (void)rec;
                (void)u;
                (void)v;
                (void)point;

                return Math::Vector3D(0, 0, 0);
            }

            /**
            * @brief This function is used to calculate the probability density function
            * A AMaterial can't calculate the probability density function, so it returns 0
            * @param ray
            * @param rec
            * @param scattered
            * @return double
            */
            virtual double scattering_pdf(const Ray &ray, const HitRecord &rec, const Ray &scattered) const
            {
                (void)ray;
                (void)rec;
                (void)scattered;

                return 0;
            }

            virtual void init(const libconfig::Setting &setting)
            {
                (void)setting;
            }
    };
};

#endif /* !AMATERIAL_HPP_ */
