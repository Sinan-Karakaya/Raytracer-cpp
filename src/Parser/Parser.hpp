/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Parser
*/

#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <libconfig.h++>
#include <memory>
#include <list>
#include <unistd.h>
#include <filesystem>

#include "Camera.hpp"
#include "Vector3D.hpp"
#include "IPrimitive.hpp"
#include "LibLoader.hpp"
#include "PrimitiveList.hpp"
#include "Transform.hpp"

#define LIBLOADER_CONFIG_FILE "config/libloader.cfg"
#define LIB_FOLDER "/lib/"

struct CameraValues {
    int width;
    int height;
    Math::Vector3D look_from;
    Math::Vector3D look_at;
    Math::Vector3D up;
    double fov;
    double aspect;
    double aperture;
    double disk;
    int sample;
    Math::Vector3D background;
};

class Parser {
    public:
        // Constructor & Destructor
        Parser(const std::string &filename, bool debugMode = false);
        ~Parser() = default;

        // Methods
        void parseConfigFile();
        void parseCamera(const libconfig::Setting &camera);
        void parsePrimitives(const libconfig::Setting &primitives);
        void parseLights(const libconfig::Setting &lights);
        void parsePrimitive(const libconfig::Setting &sphere, const std::string &filename, const std::string &entryPoint, RayTracer::Geometry::PrimitiveList &list);
        std::string removeExtension(const std::string &filename);

        // Getters & Setters
        const struct CameraValues &getCameraValues() const;
        const std::string &getFilename() const;

        // Dump
        void dump() const;
        void dumpFilename() const;
        void dumpPrimitives(const std::string &blockName, const std::string &libName,
                            const std::string &entryPoint) const;
        void dumpCameraValues() const;

        const RayTracer::Geometry::PrimitiveList &getPrimitives() const { return _primitives; }
        const RayTracer::Geometry::PrimitiveList &getLights() const { return _lights; }

    private:
        struct CameraValues _cameraValues;

        std::string _filename;
        libconfig::Config _cfg;
        libconfig::Config _libloaderCfg;

        RayTracer::Geometry::PrimitiveList _primitives;
        RayTracer::Geometry::PrimitiveList _lights;
        bool _debugMode;

};
// Exceptions
class ParserException : public std::exception {
    public:
        ParserException(const std::string &message) : _message(message) {};
        ~ParserException() = default;
        const char *what() const noexcept override { return _message.c_str(); }
    private:
        std::string _message;
};

#endif /* !PARSER_HPP_ */
