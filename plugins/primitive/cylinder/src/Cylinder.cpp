/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Cylinder
*/

#include "Cylinder.hpp"

namespace RayTracer::Geometry {
    ///////////////////////
    // Infinite Cylinder //
    ///////////////////////
    Cylinder::Cylinder()
    {
    }

    Cylinder::~Cylinder()
    {
        //if (material)
        //    delete material;
    }

    bool Cylinder::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        // Transform the ray into the local coordinate system of the cylinder
        Ray localRay = ray.transformed(rotation.conjugate(), center);

        double a = localRay.getDirection().x * localRay.getDirection().x + localRay.getDirection().y * localRay.getDirection().y;
        double b = 2.0f * (localRay.getDirection().x * localRay.getOrigin().x + localRay.getDirection().y * localRay.getOrigin().y);
        double c = localRay.getOrigin().x * localRay.getOrigin().x + localRay.getOrigin().y * localRay.getOrigin().y - radius * radius;
        double discriminant = b * b - 4.0f * a * c;

        if (discriminant < 0)
            return false;

        double t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0f * a);

        // Check if the ray hits the sides of the cylinder
        bool hitSides = false;
        if (t1 > t_min && t1 < t_max) {
            double z = localRay.getOrigin().z + localRay.getDirection().z * t1;

            if (z > (center.z - MAXFLOAT / 2) && z < (center.z + MAXFLOAT / 2)) {
                hitSides = true;
                rec.t = t1;
                rec.point = ray.getPoint(t1);
                rec.setFaceNormal(ray, (rec.point - center).normalize());
                if (rec.normal.dot(-ray.getDirection()) < 0)
                    rec.normal = -rec.normal;
            }
        }

        if (t2 > t_min && t2 < t_max) {
            double z = localRay.getOrigin().z + localRay.getDirection().z * t2;

            if (z > (center.z - MAXFLOAT / 2) && z < (center.z + MAXFLOAT / 2)) {
                if (hitSides && t2 < rec.t) {
                    // The ray hits the cylinder on both sides, but t2 is closer than t1
                    rec.t = t2;
                    rec.point = ray.getPoint(t2);
                    rec.setFaceNormal(ray, (rec.point - center).normalize());
                    if (rec.normal.dot(-ray.getDirection()) < 0)
                        rec.normal = -rec.normal;
                } else if (!hitSides) {
                    // The ray only hits the cylinder on one side
                    hitSides = true;
                    rec.t = t2;
                    rec.point = ray.getPoint(t2);
                    rec.setFaceNormal(ray, (rec.point - center).normalize());
                    if (rec.normal.dot(-ray.getDirection()) < 0)
                        rec.normal = -rec.normal;
                }
            }
        }

        if (!hitSides)
            return false;
        rec.material = material;
        return true;
    }

    bool Cylinder::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        (void)time0;
        (void)time1;

        Math::Vector3D min = rotation.rotate(rotation, _box.getMin()) + center;
        Math::Vector3D max = rotation.rotate(rotation, _box.getMax()) + center;

        box = Math::AABB(min, max);
        return true;
    }

    void Cylinder::builder(const libconfig::Setting &settings)
    {
        Math::Vector3D axis;
        Math::AABB box;
        double degrees = 0.0f;
        Tools tools;

        center = Math::Vector3D(settings["center"]["x"], settings["center"]["y"], settings["center"]["z"]);
        radius = settings["radius"];
        rotation = Math::Quaternion();
        axis = Math::Vector3D(settings["axis"]["x"], settings["axis"]["y"], settings["axis"]["z"]);
        degrees = settings["rotation"];
        rotation = rotation.from_axis_angle(axis, degrees * M_PI / 180);

        std::string materialName = settings["material"]["name"];
        if (materialName == "Lambertian") {
            if (settings["material"].exists("texture")) {
                std::string textureName = settings["material"]["texture"]["name"];
                if (textureName == "solidColor") {
                    ITexture *texture = new SolidColor(Math::Vector3D(settings["material"]["texture"]["color"]["r"],
                                                                        settings["material"]["texture"]["color"]["g"],
                                                                        settings["material"]["texture"]["color"]["b"]));
                    material = new Lambertian(texture);
                } else
                    material = new Lambertian(tools.loadTexture(settings["material"]["texture"]));
            } else {
                Math::Vector3D albedo = Math::Vector3D(settings["material"]["color"]["r"],
                                                        settings["material"]["color"]["g"],
                                                        settings["material"]["color"]["b"]);
                material = new Lambertian(albedo);
            }
        } else
            material = loadMaterial(settings);

        if (bounding_box(0.0f, 1.0f, box))
            _box = box;
        else
            _box = Math::AABB(Math::Vector3D(0.0f, 0.0f, 0.0f), Math::Vector3D(0.0f, 0.0f, 0.0f));
    }
};

extern "C" RayTracer::Geometry::Cylinder *EntryCylinderPoint()
{
    return new RayTracer::Geometry::Cylinder();
}