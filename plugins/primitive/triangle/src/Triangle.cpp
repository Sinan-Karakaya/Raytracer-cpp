/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Triangle
*/

#include "Triangle.hpp"

namespace RayTracer::Geometry {
        Triangle::Triangle(Math::Vector3D pa, Math::Vector3D pb, Math::Vector3D pc, IMaterial *material) : _pa(pa), _pb(pb), _pc(pc), _material(material) {};

    Triangle::~Triangle() {};

    bool Triangle::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        // Compute the plane's normal
        Math::Vector3D edge1 = _pb - _pa;
        Math::Vector3D edge2 = _pc - _pa;
        Math::Vector3D normal = edge1.cross(edge2);

        // Finding the intersection point
        // Check if ray and plane are parallel
        double NdotRayDirection = normal.dot(ray.getDirection());

        if (fabs(NdotRayDirection) < t_min)
            return false;

        double determinant = -normal.dot(_pa);
        double t = -(normal.dot(ray.getOrigin()) + determinant) / NdotRayDirection;

        // Check if the triangle is in behind the ray
        if (t < t_min || t > t_max)
            return false;
        
        // Compute the intersection point
        Math::Vector3D point = ray.getOrigin() + ray.getDirection() * t;

        // Inside-outside test
        Math::Vector3D c;

        Math::Vector3D edge0 = _pb - _pa;
        Math::Vector3D vp0 = point - _pa;
        c = edge0.cross(vp0);

        if (normal.dot(c) < 0)
            return false; // Intersection is on the right side

        edge1 = _pc - _pb;
        Math::Vector3D vp1 = point - _pb;
        c = edge1.cross(vp1);

        if (normal.dot(c) < 0)
            return false; // Intersection is on the right side

        edge2 = _pa - _pc;
        Math::Vector3D vp2 = point - _pc;
        c = edge2.cross(vp2);

        if (normal.dot(c) < 0)
            return false; // Intersection is on the right side

        rec.t = t;
        rec.point = point;
        rec.setFaceNormal(ray, normal);
        rec.material = _material;
        return true;
    }

    bool Triangle::bounding_box(double t0, double t1, Math::AABB &box) const
    {
        (void)t0;
        (void)t1;

        Math::Vector3D min = Math::Vector3D(
            std::min(_pa.x, std::min(_pb.x, _pc.x)),
            std::min(_pa.y, std::min(_pb.y, _pc.y)),
            std::min(_pa.z, std::min(_pb.z, _pc.z))
        );

        Math::Vector3D max = Math::Vector3D(
            std::max(_pa.x, std::max(_pb.x, _pc.x)),
            std::max(_pa.y, std::max(_pb.y, _pc.y)),
            std::max(_pa.z, std::max(_pb.z, _pc.z))
        );

        box = Math::AABB(min, max);
        return true;
    }

    void Triangle::builder(const libconfig::Setting &setting)
    {
        _pa = Math::Vector3D(setting["pa"]["x"], setting["pa"]["y"], setting["pa"]["z"]);
        _pb = Math::Vector3D(setting["pb"]["x"], setting["pb"]["y"], setting["pb"]["z"]);
        _pc = Math::Vector3D(setting["pc"]["x"], setting["pc"]["y"], setting["pc"]["z"]);

        std::string material = setting["material"]["name"];
        if (material == "Lambertian") {
            Math::Vector3D albedo = Math::Vector3D(setting["material"]["color"]["r"],
                                                   setting["material"]["color"]["g"],
                                                   setting["material"]["color"]["b"]);
            _material = new Lambertian(albedo);
        } else
            _material = loadMaterial(setting);
    }
};
