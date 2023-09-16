/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Cube
*/

#include "Cube.hpp"

namespace RayTracer::Geometry {
    Cube::Cube()
    {
        // IPrimitive **box = new IPrimitive*[CUBESIDES];

        // box[0] = new XYRectangle(p0.x, p1.x, p0.y, p1.y, p1.z, material);
        // box[1] = new XYRectangle(p0.x, p1.x, p0.y, p1.y, p0.z, material);
        // box[2] = new XZRectangle(p0.x, p1.x, p0.z, p1.z, p1.y, material);
        // box[3] = new XZRectangle(p0.x, p1.x, p0.z, p1.z, p0.y, material);
        // box[4] = new YZRectangle(p0.y, p1.y, p0.z, p1.z, p1.x, material);
        // box[5] = new YZRectangle(p0.y, p1.y, p0.z, p1.z, p0.x, material);

        // _sides = new PrimitiveList(box, CUBESIDES);
    }

    Cube::~Cube()
    {
        delete _sides;
    }

    bool Cube::hit(const Ray& ray, double t_min, double t_max, HitRecord& rec) const
    {
        return _sides->hit(ray, t_min, t_max, rec);
    }

    bool Cube::bounding_box(double time0, double time1, Math::AABB &box) const
    {
        (void)time0;
        (void)time1;
        box = Math::AABB(_minBox, _maxBox);
        return true;
    }

    void Cube::builder(const libconfig::Setting &settings)
    {
        IPrimitive **box = new IPrimitive*[CUBESIDES];
        Math::Vector3D p0 = Math::Vector3D(settings["p0"]["x"], settings["p0"]["y"], settings["p0"]["z"]);
        Math::Vector3D p1 = Math::Vector3D(settings["p1"]["x"], settings["p1"]["y"], settings["p1"]["z"]);
        IMaterial *material;
        Tools tools;

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

        box[0] = new XYRectangle(p0.x, p1.x, p0.y, p1.y, p1.z, material);
        box[1] = new XYRectangle(p0.x, p1.x, p0.y, p1.y, p0.z, material);
        box[2] = new XZRectangle(p0.x, p1.x, p0.z, p1.z, p1.y, material);
        box[3] = new XZRectangle(p0.x, p1.x, p0.z, p1.z, p0.y, material);
        box[4] = new YZRectangle(p0.y, p1.y, p0.z, p1.z, p1.x, material);
        box[5] = new YZRectangle(p0.y, p1.y, p0.z, p1.z, p0.x, material);

        _sides = new PrimitiveList(box, CUBESIDES);
    }
};

extern "C" {
    RayTracer::Geometry::Cube *EntryCubePoint()
    {
        return new RayTracer::Geometry::Cube();
    }
}
