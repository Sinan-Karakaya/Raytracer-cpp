/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** Scene
*/

#pragma once

#include <vector>

#include "PrimitiveList.hpp"
#include "IRenderer.hpp"
#include "IMaterial.hpp"
#include "ILight.hpp"
#include "Camera.hpp"

namespace RayTracer {
    class Scene {
        public:
            Scene() = default;
        Scene(const Camera &camera, const Geometry::PrimitiveList &primitiveList)
                : _camera(camera), _primitiveList(primitiveList) {};
            Scene(const Camera &camera, const Geometry::PrimitiveList &primitiveList, const Geometry::PrimitiveList &lightList)
                : _camera(camera), _primitiveList(primitiveList), _lightList(lightList) {};
            ~Scene() = default;

            Camera getCamera() const { return _camera; };
            const Geometry::PrimitiveList &getPrimitiveList() const { return _primitiveList; };
            const Geometry::PrimitiveList &getLightList() const { return _lightList; };

        private:
            Camera _camera;
            Geometry::PrimitiveList _primitiveList;
            Geometry::PrimitiveList _lightList;
    };
} // RayTracer
