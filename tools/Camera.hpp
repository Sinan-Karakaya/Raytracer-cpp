/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Tools.hpp"
#include "Ray.hpp"

namespace RayTracer {
    class Camera {
        public:
            Camera() = default;
            Camera(Math::Vector3D look_from, Math::Vector3D look_at, Math::Vector3D up, double fov, double aspect,
                double aperture, double disk, double time0 = 0.0f, double time1 = 0.0f, int width = 0, int height = 0, int sample = 0)
            {
                double theta = fov * M_PI / 180;
                double half_height = tan(theta / 2.0f);
                double viewport_h = 2.0f * half_height;
                double viewport_w = aspect * viewport_h;

                w = (look_from - look_at).unitVector();
                u = up.cross(w).unitVector();
                v = w.cross(u);

                origin = look_from;
                horizontal = u * (viewport_w * disk);
                vertical = v * (viewport_h * disk);

                lower_left_corner = origin - horizontal / 2 - vertical / 2 - w * disk;
                len_radius = aperture / 2.0f;
                rendWidth = width;
                rendHeight = height;
                samples = sample;
            }
            Camera(const Camera &camera)
            {
                this->lower_left_corner = camera.lower_left_corner;
                this->horizontal = camera.horizontal;
                this->vertical = camera.vertical;
                this->origin = camera.origin;
                this->len_radius = camera.len_radius;
                this->u = camera.u;
                this->v = camera.v;
                this->w = camera.w;
                this->rendWidth = camera.rendWidth;
                this->rendHeight = camera.rendHeight;
                this->time0 = camera.time0;
                this->time1 = camera.time1;
                this->samples = camera.samples;
            }
            ~Camera() = default;
            Math::Vector3D random_unit_disk() { return Math::Vector3D(); };

            Ray getRay(double u, double v)
            {
                Tools toolBox;
                Math::Vector3D rd = toolBox.randomUnitVector() * len_radius;
                Math::Vector3D offset = u * rd.x + v * rd.y;

                return Ray(origin + offset, lower_left_corner + horizontal * u + vertical * v - origin - offset);
            };

            Camera &operator=(const Camera &other)
            {
                this->lower_left_corner = other.lower_left_corner;
                this->horizontal = other.horizontal;
                this->vertical = other.vertical;
                this->origin = other.origin;
                this->len_radius = other.len_radius;
                this->u = other.u;
                this->v = other.v;
                this->w = other.w;
                this->rendWidth = other.rendWidth;
                this->rendHeight = other.rendHeight;
                this->time0 = other.time0;
                this->time1 = other.time1;
                this->samples = other.samples;

                return *this;
            }

            Math::Vector3D background;
            Math::Vector3D lower_left_corner;
            Math::Vector3D horizontal;
            Math::Vector3D vertical;
            Math::Vector3D origin;

            double len_radius;

            Math::Vector3D u;
            Math::Vector3D v;
            Math::Vector3D w;

            int rendWidth;
            int rendHeight;
            int samples;

            double time0;
            double time1;
        };
};

#endif /* !CAMERA_HPP_ */
