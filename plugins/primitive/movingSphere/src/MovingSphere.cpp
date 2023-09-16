/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** MovingSphere
*/

#include "MovingSphere.hpp"

namespace RayTracer::Geometry {
    MovingSphere::MovingSphere() {}

    MovingSphere::~MovingSphere()
    {
    }

    bool MovingSphere::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        Math::Vector3D oc = ray.getOrigin() - getCenter(ray.getTime());

        double a = ray.getDirection().lengthSquared();
        double b = oc.dot(ray.getDirection());
        double c = oc.lengthSquared() - _radius * _radius;
        double discriminant = b * b - a * c;
        double solution = 0.0f;

        if (discriminant < 0)
            return false;
        discriminant = sqrt(discriminant);

        solution = (-b - discriminant) / a;

        if (solution < t_min  || t_max < solution) {
            solution = (-b + discriminant) / a;
            if (solution < t_min || t_max < solution)
                return false;
        }

        rec.t = solution;
        rec.point = ray.getPoint(rec.t);
        rec.setFaceNormal(ray, (rec.point - getCenter(ray.getTime())) / _radius);
        rec.material = _material;
        return true;
    }

    bool MovingSphere::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        Math::AABB box0 = Math::AABB(getCenter(time0) - Math::Vector3D(_radius, _radius, _radius), getCenter(time0) + Math::Vector3D(_radius, _radius, _radius));
        Math::AABB box1 = Math::AABB(getCenter(time1) - Math::Vector3D(_radius, _radius, _radius), getCenter(time1) + Math::Vector3D(_radius, _radius, _radius));

        box = box0.surrounding_box(box1);
        return true;
    }

    Math::Vector3D MovingSphere::getCenter(double time) const
    {
        return _center0 + ((_center1 - _center0) * ((time - _time0) / (_time1 - _time0)));
    }

    void MovingSphere::builder(const libconfig::Setting &settings)
    {
        Tools tools;
        _center0 = Math::Vector3D(settings["center0"]["x"], settings["center0"]["y"], settings["center0"]["z"]);
        _center1 = Math::Vector3D(settings["center1"]["x"], settings["center1"]["y"], settings["center1"]["z"]);

        _time0 = settings["time0"];
        _time1 = settings["time1"];
        _radius = settings["radius"];

        std::string material = settings["material"]["name"];
        if (material == "Lambertian") {
            if (settings["material"].exists("texture")) {
                std::string textureName = settings["material"]["texture"]["name"];
                if (textureName == "solidColor") {
                    ITexture *texture = new SolidColor(Math::Vector3D(settings["material"]["texture"]["color"]["r"],
                                                                        settings["material"]["texture"]["color"]["g"],
                                                                        settings["material"]["texture"]["color"]["b"]));
                    _material = new Lambertian(texture);
                } else
                    _material = new Lambertian(tools.loadTexture(settings["material"]["texture"]));
            } else {
                Math::Vector3D albedo = Math::Vector3D(settings["material"]["color"]["r"],
                                                        settings["material"]["color"]["g"],
                                                        settings["material"]["color"]["b"]);
                _material = new Lambertian(albedo);
            }
        } else
            _material = loadMaterial(settings);
    }
};

extern "C" {
    RayTracer::Geometry::MovingSphere *EntryMovingSpherePoint()
    {
        return new RayTracer::Geometry::MovingSphere();
    }
}
