/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** IRenderer
*/

#pragma once

#include <memory>
#include "PrimitiveList.hpp"
#include "Scene.hpp"

namespace RayTracer::Plugin
{
    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void render() = 0;

        virtual void setScene(std::shared_ptr<RayTracer::Scene> scene) = 0;
    };
} // Plugin
