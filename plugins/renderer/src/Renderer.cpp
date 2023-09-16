/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** Renderer
*/

#include "Renderer.hpp"

namespace RayTracer
{
    namespace Plugin
    {
        Math::Vector3D Renderer::color(const RayTracer::Ray &ray, const Math::Vector3D
        &background, RayTracer::Geometry::IPrimitive *lights, RayTracer::Geometry::IPrimitive *world, int depth)
        {
            RayTracer::HitRecord rec;

            if (depth <= 0)
                return Math::Vector3D(0, 0, 0);
            if (!world || !world->hit(ray, 0.001, MAXFLOAT, rec))
                return background;
            RayTracer::ScatterRecord srec;
            RayTracer::Ray scattered;
            Math::Vector3D emitted = rec.material->emitted(ray, rec, rec.u, rec.v, rec.point);
            double pdf = 0.0f;

            if (!rec.material->scatter(ray, rec, srec))
                return emitted;
            if (srec.isSpecular)
                return srec.attenuation * color(srec.specularRay, background, lights, world, depth - 1);

            RayTracer::IPDF *light = new RayTracer::PrimitivePDF(lights, rec.point);
            RayTracer::IPDF *mixture = new RayTracer::MixturePDF(light, srec.pdf);

            scattered = RayTracer::Ray(rec.point, mixture->generate(), ray.getTime());
            pdf = mixture->value(scattered.getDirection());

            delete light;
            delete mixture;
            delete srec.pdf;

            return emitted + srec.attenuation * rec.material->scattering_pdf(ray, rec, scattered) * color(scattered,
                background, lights, world, depth - 1) / pdf;
        }

        void Renderer::renderThread(int start, int end, int id)
        {
            RayTracer::HitRecord rec;

            std::cout << "Thread " << id << " started" << std::endl;

            for (int y = start; y < end; y++) {
                for (int x = 0; x < _camera->rendWidth; x++) {
                    Math::Vector3D pixel_colors(0.0, 0.0, 0.0);
                    for (int s = 0; s < _camera->samples; s++) {
                        double u = double(x + drand48()) / double(_camera->rendWidth - 1);
                        double v = double(y + drand48()) / double(_camera->rendHeight - 1);
                        RayTracer::Ray ray = _camera->getRay(u, v);
                        pixel_colors += color(ray, Math::Vector3D(0.7, 0.8, 1.0), &_lights, &_world, 50);
                    }
                    pixel_colors /= double(_camera->samples);
                    pixel_colors.x = sqrt(pixel_colors.x);
                    pixel_colors.y = sqrt(pixel_colors.y);
                    pixel_colors.z = sqrt(pixel_colors.z);
                    _fbMutex.lock();
                    _fb[y * _camera->rendWidth + x] = pixel_colors;
                    _fbMutex.unlock();
                }
                _scanlinesRemaining--;
            }
            std::cout << "Thread " << id << " ended" << std::endl;
        }

        void Renderer::progressUpdate()
        {
            auto startTime = std::chrono::steady_clock::now();

            while (_scanlinesRemaining >= 0) {
                int remaining = _scanlinesRemaining.load();
                double elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::steady_clock::now() - startTime).count();
                double secondsPerScanline = elapsedSeconds / (_camera->rendHeight - remaining);
                _timeLeft = secondsPerScanline * remaining;

                _estimatedTime.store(_timeLeft);

                std::cerr << "\rScanlines remaining: " << remaining << " on " << _camera->rendHeight
                          << " lines. Estimated time left: " << _timeLeft << " seconds." << std::flush;

                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            std::cerr << std::endl;
            _timeLeft = 0.0;
        }

        void Renderer::render()
        {
            this->_start = clock();

            _fbMutex.lock();
            _fb.reserve(_camera->rendWidth * _camera->rendHeight);
            for (int i = 0; i < _camera->rendWidth * _camera->rendHeight; i++)
                _fb.push_back(Math::Vector3D(0.0, 0.0, 0.0));
            _fbMutex.unlock();

            try {
              _preview = std::make_unique<RendererPreview>(_camera->rendWidth, _camera->rendHeight, _fb, _fbMutex,
                                                           _timeLeft);
            } catch (std::runtime_error &e) {
              std::cerr << e.what() << std::endl;
              return;
            }
            std::thread previewThread(&RendererPreview::update, _preview.get());

            std::vector<std::thread> threads(_nThreads);
            for (int i = 0; i < _nThreads; i++) {
                int start = i * (_camera->rendHeight / _nThreads);
                int end = (i + 1) * (_camera->rendHeight / _nThreads);

                // Account for the remaining scanlines
                if (i == _nThreads - 1)
                    end = _camera->rendHeight;

                std::thread thread(&Renderer::renderThread, this, start, end, i);
                threads[i] = std::move(thread);
            }

            progressUpdate();

            for (auto &thread : threads)
                thread.join();

            this->_stop = clock();
            this->_elapsed = ((double)(this->_stop - this->_start)) / CLOCKS_PER_SEC;
            std::cerr << " It took " << this->_elapsed << " seconds.\n";
            previewThread.join();
        }
    } // RayTracer
} // Plugin

extern "C" {
    RayTracer::Plugin::IRenderer *EntryRendererPoint()
    {
        return new RayTracer::Plugin::Renderer();
    }
}
