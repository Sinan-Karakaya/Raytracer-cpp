/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** APrimitive
*/

#ifndef APRIMITIVE_HPP_
    #define APRIMITIVE_HPP_

    #include "IPrimitive.hpp"

    #include <filesystem>
    #include "Tools.hpp"

namespace RayTracer::Geometry {
    class APrimitive : public IPrimitive {
        public:

            virtual ~APrimitive() override = default;

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

            virtual double pdfValue(const Math::Vector3D &origin, const Math::Vector3D &direction) const override
            {
                (void)origin;
                (void)direction;

                return 0;
            }

            virtual Math::Vector3D random(const Math::Vector3D &origin) const override
            {
                (void)origin;

                return Math::Vector3D(1, 0, 0);
            }

            virtual void builder(const libconfig::Setting &setting) = 0;

            virtual IMaterial *loadMaterial(const libconfig::Setting &setting) override
            {
                std::filesystem::path currentDir = std::filesystem::current_path();
                const std::string pwd = std::string(currentDir.c_str());
                std::string libname = setting["material"]["name"];
                if (libname.empty() || libname == "none")
                    return new AMaterial();

                std::transform(libname.begin(), libname.end(), libname.begin(), ::tolower);
                libname = "raytracer_" + libname + ".so";
                void *handle = LibLoader<IPrimitive>::openModule(pwd + "/lib/" + libname);
                if (!handle)
                    return new AMaterial();
                IMaterial *mat = LibLoader<IMaterial>::loadModule(handle, "EntryPoint");
                mat->init(setting);
                LibLoader<IMaterial>::closeModule(handle);
                return mat;
            }

            // virtual
    };
};

#endif /* !APRIMITIVE_HPP_ */
