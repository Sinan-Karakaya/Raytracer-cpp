/*
** EPITECH PROJECT, 2023
** RayTracer
** File description:
** Plane
*/

#include "Planes.hpp"

namespace RayTracer::Geometry {
    Plane::Plane(const std::string &axis, double position, IMaterial *material) : _position(position),
    _material(material)
    {
        if (axis.compare("X"))
            _normal = Math::Vector3D(1, 0, 0);
        else if (axis.compare("Y"))
            _normal = Math::Vector3D(0, 1, 0);
        else if (axis.compare("Z"))
            _normal = Math::Vector3D(0, 0, 1);
        else
            std::cerr << "Error: Plane axis must be X, Y or Z" << std::endl;
    }

    Plane::~Plane()
    {
        delete _material;
    };

    bool Plane::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        double denominator = ray.getDirection().dot(_normal);
        double t = (_position - ray.getOrigin().dot(_normal)) / denominator;

        if (denominator == 0)
            return false;
        if (t < t_min || t > t_max)
            return false;

        rec.t = t;
        rec.point = ray.getPoint(t);
        rec.setFaceNormal(ray, _normal);
        rec.material = _material;
        return true;
    }

    bool Plane::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        (void)time0;
        (void)time1;

        box = Math::AABB(Math::Vector3D(_position - 0.0001, _position + 0.0001), _normal);
        return true;
    }

    void Plane::builder(const libconfig::Setting &setting)
    {
        std::string axis = setting["axis"];
        Tools tools;

        if (axis.compare("X"))
            _normal = Math::Vector3D(1, 0, 0);
        else if (axis.compare("Y"))
            _normal = Math::Vector3D(0, 1, 0);
        else if (axis.compare("Z"))
            _normal = Math::Vector3D(0, 0, 1);
        _position = setting["position"];

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
    RayTracer::Geometry::Plane *EntryPlanePoint(const std::string &axis, double position, RayTracer::IMaterial *material)
    {
        return new RayTracer::Geometry::Plane(axis, position, material);
    }
}
