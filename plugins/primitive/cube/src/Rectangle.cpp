/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

namespace RayTracer::Geometry {
    /////////////////
    // XYRectangle //
    /////////////////
    XYRectangle::XYRectangle(double p0, double p1, double p2, double p3, double k, IMaterial *material) : x0(p0), x1
    (p1), y0(p2), y1(p3), k(k), material(material) {}

    XYRectangle::~XYRectangle()
    {
        delete material;
    }

    bool XYRectangle::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        double t = (k - ray.getOrigin().z) / ray.getDirection().z;

        if (t < t_min || t > t_max)
            return false;
        double x = ray.getOrigin().x + t * ray.getDirection().x;
        double y = ray.getOrigin().y + t * ray.getDirection().y;
        if (x < x0 || x > x1 || y < y0 || y > y1)
            return false;
        rec.u = (x - x0) / (x1 - x0);
        rec.v = (y - y0) / (y1 - y0);
        rec.t = t;
        rec.material = material;
        rec.point = ray.getPoint(rec.t);
        rec.setFaceNormal(ray, Math::Vector3D(0.0f, 0.0f, 1.0f));
        return true;
    }

    bool XYRectangle::bounding_box(double time0, double time1, Math::AABB &output_box) const
    {
        (void)time0;
        (void)time1;
        output_box = Math::AABB(Math::Vector3D(x0, y0, k - 0.0001), Math::Vector3D(x1, y1, k + 0.0001));
        return true;
    }

    void XYRectangle::builder(const libconfig::Setting &setting)
    {
        Tools toolBox;
        x0 = setting["x0"];
        x1 = setting["x1"];
        y0 = setting["y0"];
        y1 = setting["y1"];
        k = setting["k"];

        std::string materialName = setting["material"]["name"];
        if (materialName == "Lambertian") {
            if (setting["material"].exists("texture")) {
                std::string textureName = setting["material"]["texture"]["name"];
                if (textureName == "solidColor") {
                    ITexture *texture = new SolidColor(Math::Vector3D(setting["material"]["texture"]["color"]["r"],
                                                                        setting["material"]["texture"]["color"]["g"],
                                                                        setting["material"]["texture"]["color"]["b"]));
                    material = new Lambertian(texture);
                } else
                    material = new Lambertian(toolBox.loadTexture(setting["material"]["texture"]));
            } else {
                Math::Vector3D albedo = Math::Vector3D(setting["material"]["color"]["r"],
                                                        setting["material"]["color"]["g"],
                                                        setting["material"]["color"]["b"]);
                material = new Lambertian(albedo);
            }
        } else
            material = loadMaterial(setting);
    }

    /////////////////
    // XZRectangle //
    /////////////////
    XZRectangle::XZRectangle(double p0, double p1, double p2, double p3, double k, IMaterial *material) : x0(p0), x1
    (p1), z0(p2), z1(p3), k(k), material(material) {}

    XZRectangle::~XZRectangle()
    {
        delete material;
    }

    bool XZRectangle::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        double t = (k - ray.getOrigin().y) / ray.getDirection().y;

        if (t < t_min || t > t_max)
            return false;
        double x = ray.getOrigin().x + t * ray.getDirection().x;
        double z = ray.getOrigin().z + t * ray.getDirection().z;
        if (x < x0 || x > x1 || z < z0 || z > z1)
            return false;
        rec.u = (x - x0) / (x1 - x0);
        rec.v = (z - z0) / (z1 - z0);
        rec.t = t;
        rec.material = material;
        rec.point = ray.getPoint(rec.t);
        rec.setFaceNormal(ray, Math::Vector3D(0.0f, 1.0f, 0.0f));
        return true;
    }

    bool XZRectangle::bounding_box(double time0, double time1, Math::AABB &output_box) const
    {
        (void)time0;
        (void)time1;
        output_box = Math::AABB(Math::Vector3D(x0, k - 0.0001, z0), Math::Vector3D(x1, k + 0.0001, z1));
        return true;
    }

    double XZRectangle::pdfValue(const Math::Vector3D& origin, const Math::Vector3D& v) const
    {
        HitRecord rec;

        if (!hit(Ray(origin, v), 0.001, MAXFLOAT, rec))
            return 0;

        double area = (x1 - x0) * (z1 - z0);
        double distanceSquared = rec.t * rec.t * v.lengthSquared();
        double cosine = fabs(v.dot(rec.normal) / v.length());

        return distanceSquared / (cosine * area);
    }

    Math::Vector3D XZRectangle::random(const Math::Vector3D& origin) const
    {
        Tools toolBox;

        Math::Vector3D random_point = Math::Vector3D(toolBox.randomDouble(x0, x1), k, toolBox.randomDouble(z0, z1));

        return random_point - origin;
    }

    void XZRectangle::builder(const libconfig::Setting &setting)
    {
        Tools toolBox;
        x0 = setting["x0"];
        x1 = setting["x1"];
        z0 = setting["z0"];
        z1 = setting["z1"];
        k = setting["k"];

        std::string materialName = setting["material"]["name"];
        if (materialName == "Lambertian") {
            if (setting["material"].exists("texture")) {
                std::string textureName = setting["material"]["texture"]["name"];
                if (textureName == "solidColor") {
                    ITexture *texture = new SolidColor(Math::Vector3D(setting["material"]["texture"]["color"]["r"],
                                                                        setting["material"]["texture"]["color"]["g"],
                                                                        setting["material"]["texture"]["color"]["b"]));
                    material = new Lambertian(texture);
                } else
                    material = new Lambertian(toolBox.loadTexture(setting["material"]["texture"]));
            } else {
                Math::Vector3D albedo = Math::Vector3D(setting["material"]["color"]["r"],
                                                        setting["material"]["color"]["g"],
                                                        setting["material"]["color"]["b"]);
                material = new Lambertian(albedo);
            }
        } else
            material = loadMaterial(setting);
    }

    /////////////////
    // YZRectangle //
    /////////////////
    YZRectangle::YZRectangle(double p0, double p1, double p2, double p3, double k, IMaterial *material) : y0(p0), y1
    (p1), z0(p2), z1(p3), k(k), material(material) {}

    YZRectangle::~YZRectangle()
    {
        delete material;
    }

    bool YZRectangle::hit(const Ray &ray, double t_min, double t_max, HitRecord &rec) const
    {
        double t = (k - ray.getOrigin().x) / ray.getDirection().x;

        if (t < t_min || t > t_max)
            return false;
        double y = ray.getOrigin().y + t * ray.getDirection().y;
        double z = ray.getOrigin().z + t * ray.getDirection().z;
        if (y < y0 || y > y1 || z < z0 || z > z1)
            return false;
        rec.u = (y - y0) / (y1 - y0);
        rec.v = (z - z0) / (z1 - z0);
        rec.t = t;
        rec.material = material;
        rec.point = ray.getPoint(rec.t);
        rec.setFaceNormal(ray, Math::Vector3D(1.0f, 0.0f, 0.0f));
        return true;
    }

    bool YZRectangle::bounding_box(double time0, double time1, Math::AABB &output_box) const
    {
        (void)time0;
        (void)time1;
        output_box = Math::AABB(Math::Vector3D(k - 0.0001, y0, z0), Math::Vector3D(k + 0.0001, y1, z1));
        return true;
    }

    void YZRectangle::builder(const libconfig::Setting &setting)
    {
        Tools toolBox;
        y0 = setting["y0"];
        y1 = setting["y1"];
        z0 = setting["z0"];
        z1 = setting["z1"];
        k = setting["k"];

        std::string materialName = setting["material"]["name"];
        if (materialName == "Lambertian") {
            if (setting["material"].exists("texture")) {
                std::string textureName = setting["material"]["texture"]["name"];
                if (textureName == "solidColor") {
                    ITexture *texture = new SolidColor(Math::Vector3D(setting["material"]["texture"]["color"]["r"],
                                                                        setting["material"]["texture"]["color"]["g"],
                                                                        setting["material"]["texture"]["color"]["b"]));
                    material = new Lambertian(texture);
                } else
                    material = new Lambertian(toolBox.loadTexture(setting["material"]["texture"]));
            } else {
                Math::Vector3D albedo = Math::Vector3D(setting["material"]["color"]["r"],
                                                        setting["material"]["color"]["g"],
                                                        setting["material"]["color"]["b"]);
                material = new Lambertian(albedo);
            }
        } else
            material = loadMaterial(setting);
    }
};

extern "C" {
    RayTracer::Geometry::XYRectangle *EntryXYRectanglePoint(double p0, double p1, double p2, double p3, double k,
                                                   RayTracer::IMaterial *material)
    {
        return new RayTracer::Geometry::XYRectangle(p0, p1, p2, p3, k, material);
    }

    RayTracer::Geometry::XZRectangle *EntryXZRectanglePoint(double p0, double p1, double p2, double p3, double k,
                                                   RayTracer::IMaterial *material)
    {
        return new RayTracer::Geometry::XZRectangle(p0, p1, p2, p3, k, material);
    }

    RayTracer::Geometry::YZRectangle *EntryYZRectanglePoint(double p0, double p1, double p2, double p3, double k,
                                                   RayTracer::IMaterial *material)
    {
        return new RayTracer::Geometry::YZRectangle(p0, p1, p2, p3, k, material);
    }
}
