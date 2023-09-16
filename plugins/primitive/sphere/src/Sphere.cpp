/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Sphere
*/

#include "Sphere.hpp"
#include <iostream>

namespace RayTracer::Geometry {
    Sphere::Sphere(Math::Vector3D origin, double radius, IMaterial *material) : _origin(origin), _radius(radius),
    _material(material) {}

    Sphere::~Sphere()
    {
        delete _material;
    }

    bool Sphere::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        Math::Vector3D oc = ray.getOrigin() - _origin;
        double a = ray.getDirection().dot(ray.getDirection());
        double b = oc.dot(ray.getDirection());
        double c = oc.dot(oc) - _radius * _radius;
        double discriminant = b * b - a * c;
        double solution = 0.0f;

        if (discriminant > 0) {
            solution = (-b - sqrt(b * b - a * c)) / a;
            if (solution < t_max && solution > t_min) {
                rec.t = solution;
                rec.point = ray.getPoint(rec.t);
                rec.setFaceNormal(ray, ((rec.point - _origin) / _radius));
                getSphereUV(rec.normal, rec.u, rec.v);
                rec.material = _material;
                return true;
            }
            solution = (-b + sqrt(b * b - a * c)) / a;
            if (solution < t_max && solution > t_min) {
                rec.t = solution;
                rec.point = ray.getPoint(rec.t);
                rec.setFaceNormal(ray, ((rec.point - _origin) / _radius));
                getSphereUV(rec.normal, rec.u, rec.v);
                rec.material = _material;
                return true;
            }
        }
        return false;
    }

    bool Sphere::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        (void)time0;
        (void)time1;
        box = Math::AABB(_origin - Math::Vector3D(_radius, _radius, _radius), _origin + Math::Vector3D(_radius, _radius, _radius));
        return true;
    }

    double Sphere::pdfValue(const Math::Vector3D &origin, const Math::Vector3D &direction) const
    {
        HitRecord rec;

        if (!hit(Ray(origin, direction), 0.001, MAXFLOAT, rec))
            return 0;

        double cos_theta_max = sqrt(1 - _radius * _radius / (_origin - origin).lengthSquared());
        double solid_angle = 2 * M_PI * (1 - cos_theta_max);

        return 1.0f / solid_angle;
    }

    Math::Vector3D Sphere::random(const Math::Vector3D &origin) const
    {
        Tools toolBox;

        Math::Vector3D direction = _origin - origin;
        double distance_squared = direction.lengthSquared();
        ONB uvw;

        uvw.buildFromW(direction);
        return uvw.local(toolBox.randomToSphere(_radius, distance_squared));
    }

    void Sphere::getSphereUV(const Math::Vector3D &point, double &u, double &v)
    {
        double theta = std::acos(-point.y);
        double phi = atan2(-point.z, point.x) + M_PI;

        u = phi / (2 * M_PI);
        v = theta / M_PI;
    }

    void Sphere::builder(const libconfig::Setting &setting)
    {
        Tools tools;
        int origin1 = setting["x"];
        int origin2 = setting["y"];
        int origin3 = setting["z"];
        int radius = setting["r"];
        _origin = Math::Vector3D(origin1, origin2, origin3);
        _radius = radius;

        std::string material = setting["material"]["name"];
        if (material == "Lambertian") {
            if (setting["material"].exists("texture")) {
                std::string textureName = setting["material"]["texture"]["name"];
                if (textureName == "solidColor") {
                    ITexture *texture = new SolidColor(Math::Vector3D(setting["material"]["texture"]["color"]["r"],
                                                                        setting["material"]["texture"]["color"]["g"],
                                                                        setting["material"]["texture"]["color"]["b"]));
                    _material = new Lambertian(texture);
                } else
                    _material = new Lambertian(tools.loadTexture(setting["material"]["texture"]));
            } else {
                Math::Vector3D albedo = Math::Vector3D(setting["material"]["color"]["r"],
                                                        setting["material"]["color"]["g"],
                                                        setting["material"]["color"]["b"]);
                _material = new Lambertian(albedo);
            }
        } else
            _material = loadMaterial(setting);
    }
};

extern "C" {
    RayTracer::Geometry::Sphere *EntrySpherePoint(Math::Vector3D origin, double radius, RayTracer::IMaterial *material)
    {
        return new RayTracer::Geometry::Sphere(origin, radius, material);
    }
}
