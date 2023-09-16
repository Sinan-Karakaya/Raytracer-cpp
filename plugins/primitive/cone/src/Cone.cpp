/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Cone
*/

#include "Cone.hpp"

namespace RayTracer::Geometry {
    ///////////////////
    // Infinite Cone //
    ///////////////////
    Cone::Cone() {}

    Cone::~Cone()
    {
        //if (material)
        //    delete material;
    }

    bool Cone::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        // Transform the ray into the local coordinate system of the cylinder
        Ray localRay = ray.transformed(rotation.conjugate(), origin);

        double a = pow(localRay.getDirection().x, 2.0f) - pow(localRay.getDirection().y, 2.0f) + pow(localRay.getDirection().z, 2.0f);
        double b = 2 * localRay.getOrigin().x * localRay.getDirection().x - 2 * localRay.getOrigin().y * localRay.getDirection().y + 2 * localRay.getOrigin().z * localRay.getDirection().z;
        double c = pow(localRay.getOrigin().x, 2.0) - pow(localRay.getOrigin().y, 2.0) + pow(localRay.getOrigin().z, 2.0);

        if (fabs(a) < EPSILON || (fabs(a) < EPSILON && fabs(b) > EPSILON))
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

        return false;
    }

    bool Cone::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        (void)time0;
        (void)time1;

        Math::Vector3D min(origin.x - radius, origin.y, origin.z - radius);
        Math::Vector3D max(origin.x + radius, MAXFLOAT, origin.z + radius);

        box = Math::AABB(min, max);
        return true;
    }

    void Cone::builder(const libconfig::Setting &settings)
    {
        Math::Vector3D axis;
        double degrees;
        Tools tools;

        origin = Math::Vector3D(settings["origin"]["x"], settings["origin"]["y"], settings["origin"]["z"]);
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
    }
};

extern "C" RayTracer::Geometry::Cone *EntryConePoint()
{
    return new RayTracer::Geometry::Cone();
}