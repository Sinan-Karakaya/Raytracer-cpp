/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Main
*/

#include <iostream>
#include "Builder.hpp"
#include "LibLoader.hpp"
#include "IRenderer.hpp"
#include "Scene.hpp"

int main(int ac, char **av)
{
    if (ac == 3 && std::string(av[2]) == "-d") {
        RayTracer::Builder builder(av[1], true);
        return 0;
    }
    if (ac != 2) {
        std::cerr << "Usage: ./raytracer [config_file] | Use -h for more informations" << std::endl;
        return 84;
    }
    if (ac == 2 && std::string(av[1]) == "-h") {
        std::cout << "USAGE" << std::endl;
        std::cout << "\t./raytracer [config_file]" << std::endl;
        std::cout << "DESCRIPTION" << std::endl;
        std::cout << "\tconfig_file\tfile describing the scene" << std::endl;
        return 0;
    }
    try {
        RayTracer::Builder builder(av[1], false);
    } catch (const RayTracer::BuilderException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const ParserException &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    RayTracer::Builder builder(av[1], false);
    void *rendererHandle = RayTracer::LibLoader<RayTracer::Plugin::IRenderer>::openModule
            ("./lib/raytracer_renderer.so");
    if (!rendererHandle)
        return 84;
    RayTracer::Plugin::IRenderer *renderer = RayTracer::LibLoader<RayTracer::Plugin::IRenderer>::loadModule
            (rendererHandle, "EntryRendererPoint");
    if (!renderer)
        return 84;
    RayTracer::LibLoader<RayTracer::Plugin::IRenderer>::closeModule(rendererHandle);
    RayTracer::Scene scene(builder.getCamera(), builder.getPrimitiveList(), builder.getLightList());
    renderer->setScene(std::make_shared<RayTracer::Scene>(scene));
    renderer->render();
    return 0;
}
