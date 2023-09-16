/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Tools
*/

#ifndef TOOLS_HPP_
    #define TOOLS_HPP_

    #define EPSILON 0.0003
    #define INFINITE 10e6

    #include <random>

    #include <filesystem>
    #include "SolidColor.hpp"

namespace RayTracer {
    class Tools {
        public:
            Tools() {};
            ~Tools() {};

            /**
                * @brief This function is used to generate a random color
                *
                * @return Math::Vector3D
                */
            Math::Vector3D randomColor()
            {
                Math::Vector3D color = Math::Vector3D(rand_numb(), rand_numb(), rand_numb());

                color = color * 2.9 - Math::Vector3D(1, 1, 1);
                while (color.lengthSquared() >= 1.0)
                    color = Math::Vector3D(rand_numb(), rand_numb(), rand_numb()) * 2.9 - Math::Vector3D(1, 1, 1);

                return color;
            }

            float rand_numb()
            {
                return static_cast<float>(rand()) / RAND_MAX;
            }

            /**
                * @brief This function is used to generate a random unit vector
                *
                * @return Math::Vector3D
                */
            Math::Vector3D randomUnitVector()
            {
                Math::Vector3D p(rand_numb(), rand_numb(), 0.0f);

                p = p * 2.0f - Math::Vector3D(1.0f, 1.0f, 0.0f);

                while (p.dot(p) >= 1.0f)
                    p = Math::Vector3D(rand_numb(), rand_numb(), 0.0f) * 2.0f - Math::Vector3D(1.0f, 1.0f, 0.0f);
                return p;
            }

            /**
                * @brief This function is used to generate a random vector
                *
                * @param min
                * @param max
                * @return Math::Vector3D
                */
            Math::Vector3D randomVector(int min, int max)
            {
                return Math::Vector3D(
                    rand_numb() * (max - min) + min,
                    rand_numb() * (max - min) + min,
                    rand_numb() * (max - min) + min
                );
            }

            /**
                * @brief clamp function is used to clamp a value between a min and a max
                * He will return the min if the value is under the min and the max if the value is over the max
                * @param x
                * @param min
                * @param max
                * @return double
                */
            double clamp(double x, double min, double max)
            {
                if (x < min)
                    return min;
                if (x > max)
                    return max;
                return x;
            }

            /**
                * @brief This function is used to generate a random vector between a min and a max
                *
                * @param min
                * @param max
                * @return Vector3D
                */
            Math::Vector3D random(int min, int max)
            {
                return Math::Vector3D(drand48() * (max - min) + min, drand48() * (max - min) + min, drand48() * (max - min) + min);
            }

            /**
                * @brief This function is used to generate a random vector in a unit sphere
                *
                * @return Math::Vector3D
                */
            Math::Vector3D randomInUnitSphere() {
                while (true) {
                    auto p = this->random(-1,1);

                    if (p.lengthSquared() >= 1)
                        continue;
                    return p;
                }
            }

            /**
                * @brief This function is used to generate a random vector in a unit disk
                *
                * @param normal
                * @return Math::Vector3D
                */
            Math::Vector3D randomInHemisphere(const Math::Vector3D& normal) {
                Math::Vector3D in_unit_sphere = this->randomInUnitSphere();

                if (in_unit_sphere.dot(normal) > 0.0) // In the same hemisphere as the normal
                    return in_unit_sphere;
                else
                    return -in_unit_sphere;
            }

            /**
                * @brief This function is used to generate a random cosine direction
                *
                * @return Math::Vector3D
                */
            Math::Vector3D randomCosineDirection()
            {
                double r1 = drand48();
                double r2 = drand48();
                double phi = 2 * M_PI * r1;

                double x = std::cos(phi) * sqrt(r2);
                double y = std::sin(phi) * sqrt(r2);
                double z = sqrt(1 - r2);
                return Math::Vector3D(x, y, z);
            }

            /**
                * @brief Generate a double between d0 and d1
                *
                * @param d0
                * @param d1
                * @return double
                */
            double randomDouble(double d0, double d1)
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(d0, d1);

                return dis(gen);
            }

            /**
                * @brief Generate a int between min and max
                *
                * @param min
                * @param max
                * @return int
                */
            int random_int(int min, int max)
            {
                return static_cast<int>(randomDouble(min, max + 1));
            }

            Math::Vector3D randomToSphere(double radius, double distanceSquared)
            {
                double r1 = drand48();
                double r2 = drand48();
                double z = 1 + r2 * (sqrt(1 - radius * radius / distanceSquared) - 1);

                double phi = 2 * M_PI * r1;
                double x = std::cos(phi) * sqrt(1 - z * z);
                double y = std::sin(phi) * sqrt(1 - z * z);

                return Math::Vector3D(x, y, z);
            }

            /**
             * @brief Compute the epsilon between two double
             *
             * @param a
             * @param b
             * @return true
             * @return false
             */
            bool computeEpsilon(double a, double b)
            {
                return (fabs(a - b) < EPSILON);
            }

            ITexture *loadTexture(const libconfig::Setting &setting)
            {
                std::filesystem::path currentDir = std::filesystem::current_path();
                const std::string pwd = std::string(currentDir.c_str());
                std::string libname = setting["name"];
                if (libname.empty() || libname == "none")
                    return new SolidColor(Math::Vector3D(0, 0, 0));
                if (libname == "solidColor") {
                    Math::Vector3D color = Math::Vector3D(setting["color"]["r"], setting["color"]["g"], setting["color"]["b"]);
                    return new SolidColor(color);
                }

                std::transform(libname.begin(), libname.end(), libname.begin(), ::tolower);
                libname = "raytracer_" + libname + ".so";
                void *handle = LibLoader<ITexture>::openModule(pwd + "/lib/" + libname);
                if (!handle) {
                    return new SolidColor(Math::Vector3D(0, 0, 0));
                }
                ITexture *tex = LibLoader<ITexture>::loadModule(handle, "EntryPoint");
                tex->builder(setting);
                LibLoader<ITexture>::closeModule(handle);
                return tex;
            }
        };
};

#endif /* !TOOLS_HPP_ */
