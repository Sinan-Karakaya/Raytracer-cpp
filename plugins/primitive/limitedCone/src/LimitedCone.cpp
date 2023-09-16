/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** LimitedCone
*/

#include "LimitedCone.hpp"

namespace RayTracer::Geometry {
    //////////////////
    // Limited Cone //
    //////////////////
    LimitedCone::LimitedCone() {}

    LimitedCone::~LimitedCone()
    {
        //if (material)
        //    delete material;
    }

bool LimitedCone::IntersectsCap(const Ray &ray, const double &t, const double &cap_radius) const
    {
        double x = ray.getOrigin().x + t * ray.getDirection().x;
        double z = ray.getOrigin().z + t * ray.getDirection().z;

        return (pow(x, 2) + pow(z, 2)) <= cap_radius + EPSILON;
    }

    bool LimitedCone::capHit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        if (fabs(ray.getDirection().y) < EPSILON)
            return false;
        double t = (-(height / 2) - ray.getOrigin().y) / ray.getDirection().y;

        if (t < t_min || t > t_max)
            return false;
        if (IntersectsCap(ray, t, fabs(-(height / 2)))) {
            rec.t = t;
            rec.point = ray.getPoint(t);
            rec.setFaceNormal(ray, Math::Vector3D(0, -1, 0));
            rec.material = material;
            return true;
        }
        t = ((height * 2) - ray.getOrigin().y) / ray.getDirection().y;
        if (t < t_min || t > t_max)
            return false;
        if (IntersectsCap(ray, t, fabs(height / 2))) {
            rec.t = t;
            rec.point = ray.getPoint(t);
            rec.setFaceNormal(ray, Math::Vector3D(0, 1, 0));
            rec.material = material;
            return true;
        }
        return false;
    }

    bool LimitedCone::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        // Transform the ray into the local coordinate system of the cylinder
        Ray localRay = ray.transformed(rotation.conjugate(), origin);

        double a = pow(localRay.getDirection().x, 2.0f) - pow(localRay.getDirection().y, 2.0f) + pow(localRay.getDirection().z, 2.0f);
        double b = 2 * localRay.getOrigin().x * localRay.getDirection().x - 2 * localRay.getOrigin().y * localRay.getDirection().y + 2 * localRay.getOrigin().z * localRay.getDirection().z;
        double c = pow(localRay.getOrigin().x, 2.0) - pow(localRay.getOrigin().y, 2.0) + pow(localRay.getOrigin().z, 2.0);

        if (fabs(a) < EPSILON && fabs(b) > EPSILON) {
            double t = -c / (2.0f * b);

            if (t < t_min || t > t_max)
                return false;
            rec.t = t;
            return capHit(localRay, t_min, t_max, rec);
        }
        if (fabs(a) < EPSILON)
            return false;
        double discriminant = pow(b, 2.0f) - 4.0f * a * c;

        if (fabs(discriminant) < EPSILON)
            discriminant = 0;
        if (discriminant < 0)
            return false;
        double sqrtDiscriminant = sqrt(discriminant);
        double t0 = (-b - sqrtDiscriminant) / (2.0f * a);
        double t1 = (-b + sqrtDiscriminant) / (2.0f * a);

        if (t0 > t1)
            std::swap(t0, t1);
        double y0 = localRay.getOrigin().y + t0 * localRay.getDirection().y;

        if (y0 < t_min || y0 > t_max) {
            rec.t = t0;
            rec.material = material;
            rec.point = ray.getPoint(t0);
            rec.setFaceNormal(ray, Math::Vector3D(0, -1, 0));
            return true;
        }
        double y1 = localRay.getOrigin().y + t1 * localRay.getDirection().y;

        if (y1 < t_min || y1 > t_max) {
            rec.t = t1;
            rec.material = material;
            rec.point = ray.getPoint(t1);
            rec.setFaceNormal(ray, Math::Vector3D(0, -1, 0));
            return true;
        }

        return capHit(localRay, t_min, t_max, rec);
    }

    bool LimitedCone::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        (void)time0;
        (void)time1;

        Math::Vector3D min(origin.x - radius, origin.y, origin.z - radius);
        Math::Vector3D max(origin.x + radius, origin.y + height, origin.z + radius);

        box = Math::AABB(min, max);
        return true;
    }

    void LimitedCone::builder(const libconfig::Setting &settings)
    {
        Math::Vector3D axis;
        double degrees;
        Tools tools;

        origin = Math::Vector3D(settings["origin"]["x"], settings["origin"]["y"], settings["origin"]["z"]);
        radius = settings["radius"];
        height = settings["height"];
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
    }
};

extern "C" RayTracer::Geometry::IPrimitive *EntryLimitedConePoint()
{
    return new RayTracer::Geometry::LimitedCone();
}
