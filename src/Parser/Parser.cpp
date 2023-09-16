/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Parser
*/

#include "Parser.hpp"


Parser::Parser(const std::string &filename, bool debugMode) : _cfg(), _libloaderCfg(), _debugMode(debugMode)
{
    try {
        _filename = removeExtension(filename);
        _cfg.readFile(filename.c_str());
        _libloaderCfg.readFile(LIBLOADER_CONFIG_FILE);
    } catch (const libconfig::FileIOException& ex) {
        throw ParserException("I/O error while reading file.");
    } catch (const libconfig::ParseException& ex) {
        std::string file = ex.getFile();
        std::string line = std::to_string(ex.getLine());
        const std::string &error = "Parse error at " + file + ":" + line + " - " + ex.getError();
        throw ParserException(error);
    }
}

void Parser::parseConfigFile()
{
    try {
        parseCamera(_cfg.lookup("camera"));
        parsePrimitives(_cfg.lookup("primitives"));
        parseLights(_cfg.lookup("lights"));

    } catch (const libconfig::SettingNotFoundException& ex) {
        throw ParserException("Setting not found: " + std::string(ex.getPath()));
    } catch (const libconfig::SettingTypeException& ex) {
        throw ParserException("Setting type error at " + std::string(ex.getPath()));
    } catch (const std::exception& ex) {
        throw ParserException("Error: " + std::string(ex.what()));
    }
}

void Parser::parseCamera(const libconfig::Setting &camera)
{
    _cameraValues.width = camera["resolution"]["width"];
    _cameraValues.height = camera["resolution"]["height"];
    _cameraValues.look_from = Math::Vector3D(camera["look_from"]["x"], camera["look_from"]["y"], camera["look_from"]["z"]);
    _cameraValues.look_at = Math::Vector3D(camera["look_at"]["x"], camera["look_at"]["y"], camera["look_at"]["z"]);
    _cameraValues.up = Math::Vector3D(camera["up"]["x"], camera["up"]["y"], camera["up"]["z"]);
    _cameraValues.fov = camera["fieldOfView"];
    double aspectW = camera["aspectRatio"]["width"];
    double aspectH = camera["aspectRatio"]["height"];
    _cameraValues.aspect = aspectW / aspectH;
    _cameraValues.aperture = camera["aperture"];
    _cameraValues.disk = camera["diskToFocus"];
    _cameraValues.sample = camera["samples"];
}

void Parser::parsePrimitives(const libconfig::Setting &primitives)
{
    const libconfig::Setting& libs = _libloaderCfg.lookup("libloader");

    for (int i = 0; i < libs["libs"].getLength(); ++i) {

        std::string blockName = libs["libs"][i]["blockName"];
        std::string libName = libs["libs"][i]["filename"];
        std::string entryPoint = libs["libs"][i]["entryPoint"];
        const libconfig::Setting& block = primitives[blockName.c_str()];

        if (_debugMode)
            dumpPrimitives(blockName, libName, entryPoint);

        for (int j = 0; j < block.getLength(); ++j) {
            parsePrimitive(block[j], libs["libs"][i]["filename"], libs["libs"][i]["entryPoint"], _primitives);
        }
    }
}

void Parser::parsePrimitive(const libconfig::Setting &primitive, const std::string &libName, const std::string &entryPoint, RayTracer::Geometry::PrimitiveList &list)
{
    std::filesystem::path currentDir = std::filesystem::current_path();
    std::string pwd = std::string(currentDir.c_str());
    void *handle = RayTracer::LibLoader<RayTracer::Geometry::IPrimitive>::openModule(pwd + LIB_FOLDER + libName.c_str());

    RayTracer::Geometry::IPrimitive *primitiveInstance =
            RayTracer::LibLoader<RayTracer::Geometry::IPrimitive>::loadModule(handle, entryPoint.c_str());
    primitiveInstance->builder(primitive);
    if (primitive.exists("transform")) {
        const libconfig::Setting& transform = primitive["transform"];
        if (transform.exists("translate")) {
            const libconfig::Setting& translate = transform["translate"];
            primitiveInstance = new RayTracer::Geometry::Translate(primitiveInstance,
                                                                   Math::Vector3D(translate["x"], translate["y"], translate["z"]));
        }
        if (transform.exists("rotate")) {
            const libconfig::Setting& rotate = transform["rotate"];
            primitiveInstance = new RayTracer::Geometry::Rotate(primitiveInstance,
                                                                rotate["degree"]);
        }
        if (transform.exists("scale")) {
            const libconfig::Setting& scale = transform["scale"];
//            primitiveInstance = new RayTracer::Geometry::Scale(primitiveInstance,
//                                                               Math::Vector3D(scale["x"], scale["y"], scale["z"]));
        }
        if (transform.exists("flipface")) {
            const libconfig::Setting& flipface = transform["flipface"];
            primitiveInstance = new RayTracer::Geometry::FlipFace(primitiveInstance);
        }
    }
    list._primitives.push_back(primitiveInstance);

    RayTracer::LibLoader<RayTracer::Geometry::IPrimitive>::closeModule(handle);
}

void Parser::parseLights(const libconfig::Setting &lights)
{
    double ambient = lights["ambient"];

    const libconfig::Setting& libs = _libloaderCfg.lookup("libloader");

    if (ambient <= 0.0)
        _cameraValues.background = Math::Vector3D(0.0f, 0.0f, 0.0f);
    else if (ambient <= 0.5)
        _cameraValues.background = Math::Vector3D(0.3f, 0.4f, 0.5f);
    else
        _cameraValues.background = Math::Vector3D(0.7f, 0.8f, 1.0f);

    for (int i = 0; i < libs["libs"].getLength(); ++i) {

        std::string blockName = libs["libs"][i]["blockName"];
        std::string libName = libs["libs"][i]["filename"];
        std::string entryPoint = libs["libs"][i]["entryPoint"];

        if (blockName == "spheres") {
            const libconfig::Setting& block = lights["point"];

            if (_debugMode)
                dumpPrimitives(blockName, libName, entryPoint);

            for (int j = 0; j < block.getLength(); ++j) {
                parsePrimitive(block[j], libs["libs"][i]["filename"], libs["libs"][i]["entryPoint"], _lights);
            }
        }
    }
}

const CameraValues &Parser::getCameraValues() const
{
    return _cameraValues;
}

std::string Parser::removeExtension(const std::string &filename)
{
    size_t lastdot = filename.find_last_of(".");
    size_t lastslash = filename.find_last_of("/");

    if (lastslash != std::string::npos)
        return removeExtension(filename.substr(lastslash + 1));
    if (lastdot == std::string::npos) {
        _filename = filename;
        return filename;
    }
    _filename = filename.substr(0, lastdot);
    return filename.substr(0, lastdot);
}

void Parser::dumpPrimitives(const std::string &blockName, const std::string &libName, const std::string &entryPoint) const
{
    std::cout << "Block name: " << blockName << std::endl;
    std::cout << "Lib name: " << libName << std::endl;
    std::cout << "Entry point: " << entryPoint << std::endl;
}

void Parser::dumpCameraValues() const
{
    std::cout << "Camera configuration:" << std::endl;
    std::cout << "Resolution: " << _cameraValues.width << "x" << _cameraValues.height << std::endl;
    std::cout << "Look from: (" << _cameraValues.look_from.x << ", " << _cameraValues.look_from.y << ", " << _cameraValues.look_from.z << ")" << std::endl;
    std::cout << "Look at: (" << _cameraValues.look_at.x << ", " << _cameraValues.look_at.y << ", " << _cameraValues.look_at.z << ")" << std::endl;
    std::cout << "Up: (" << _cameraValues.up.x << ", " << _cameraValues.up.y << ", " << _cameraValues.up.z << ")" << std::endl;
    std::cout << "Field of view: " << _cameraValues.fov << std::endl;
    std::cout << "Aspect ratio: " << _cameraValues.aspect << std::endl;
    std::cout << "Aperture: " << _cameraValues.aperture << std::endl;
    std::cout << "Disk to focus: " << _cameraValues.disk << std::endl;
    std::cout << "Samples: " << _cameraValues.sample << std::endl;
}

void Parser::dumpFilename() const
{
    std::cout << "Filename without extension: " << _filename << std::endl;
}

void Parser::dump() const
{
    dumpFilename();
    dumpCameraValues();
}

const std::string &Parser::getFilename() const
{
    return _filename;
}
