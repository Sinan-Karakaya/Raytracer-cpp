/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** RendererPreview
*/

#pragma once

#include <thread>
#include <mutex>
#include <string>
#include <fstream>
#include <iostream>
#include <atomic>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Vector3D.hpp"

#define PREVIEW_THREADS 4

namespace RayTracer::Plugin
{
    class RendererPreview
    {
    public:
        RendererPreview(int width, int height, std::vector<Math::Vector3D> &pixels, std::mutex &fbMutex, std::atomic<double>
        &remaining);
        ~RendererPreview() { ImGui::SFML::Shutdown(); };

        void update();
        void draw();

    private:
        void displayMenu();
        void writeImage(const std::string &filename);
        void writePPM(const std::string &filename);
        const char *secondsToTimeString();

    private:
        sf::RenderWindow _window;
        sf::Clock _clock;
        int _width;
        int _height;
        sf::Texture _texture;
        std::atomic<double> &_remaining;

        std::vector<Math::Vector3D> &_pixels;
        std::mutex &_fbMutex;
        std::vector<sf::Uint8> _texturePixel;
        std::string _filename = "output.png";

    };
} // Plugin
