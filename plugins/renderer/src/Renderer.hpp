/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Renderer
*/

#pragma once

#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <memory>
#include <vector>
#include <fstream>
#include <time.h>

#include "IRenderer.hpp"
#include "IMaterial.hpp"
#include "Scene.hpp"
#include "PrimitiveList.hpp"
#include "MixturePDF.hpp"
#include "PrimitivePDF.hpp"
#include "IMaterial.hpp"

#include "RendererPreview.hpp"

namespace RayTracer::Plugin
{
    class Renderer : public IRenderer
    {
    public:
        Renderer(RayTracer::Scene *scene = nullptr) : _scene(scene) {
            _nThreads = std::thread::hardware_concurrency();
            if (_nThreads == 0)
                _nThreads = 1;
            if (_scene) {
                _world = _scene->getPrimitiveList();
                _lights = _scene->getLightList();
            }
            if (_nThreads > 2)
                _nThreads -= 2;
        }
        ~Renderer() override = default;

        void render() override;

        void setScene(std::shared_ptr<RayTracer::Scene> scene) override
        {
            _scene = scene;
            _camera = std::make_shared<RayTracer::Camera>(_scene->getCamera());
            _fb.reserve(_camera->rendWidth * _camera->rendHeight);
            _world = _scene->getPrimitiveList();
            _lights = _scene->getLightList();
            _scanlinesRemaining = _camera->rendHeight;
        }

    private:
        Math::Vector3D color(const RayTracer::Ray &ray, const Math::Vector3D
        &background, RayTracer::Geometry::IPrimitive *lights, RayTracer::Geometry::IPrimitive *world, int depth);

        void renderThread(int start, int end, int id);
        void progressUpdate();

    private:
        std::vector<Math::Vector3D> _fb;
        unsigned int _nThreads;

        std::shared_ptr<RayTracer::Scene> _scene;
        std::shared_ptr<RayTracer::Camera> _camera;
        RayTracer::Geometry::PrimitiveList _world;
        RayTracer::Geometry::PrimitiveList _lights;

        std::unique_ptr<RendererPreview> _preview;
        std::mutex _fbMutex;
        std::atomic<int> _scanlinesRemaining = 0;
        std::atomic<double> _estimatedTime = 0.0;
        std::atomic<double> _timeLeft = 0.0;

        clock_t _stop;
        clock_t _start;
        double _elapsed;
    }; // class Renderer
}; // Plugin
