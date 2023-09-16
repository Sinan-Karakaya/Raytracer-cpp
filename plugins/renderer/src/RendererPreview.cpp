/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** RendererPreview
*/

#include "RendererPreview.hpp"
#include <stdexcept>

RayTracer::Plugin::RendererPreview::RendererPreview(int width, int height, std::vector<Math::Vector3D> &pixels,
                                                    std::mutex &fbMutex, std::atomic<double> &remaining)
    : _width(width), _height(height), _pixels(pixels), _fbMutex(fbMutex), _remaining(remaining)
{
    _window.create(sf::VideoMode(width, height), "RayTracer - Preview", sf::Style::Titlebar | sf::Style::Close);
    _window.setFramerateLimit(60);
    _window.setKeyRepeatEnabled(false);
    if (!ImGui::SFML::Init(_window)) {
        throw std::runtime_error("Couldn't initialize preview.");
    }

    _texture.create(width, height);
    _texture.setSmooth(true);
    _texturePixel.reserve(width * height * 4);
}

void RayTracer::Plugin::RendererPreview::update()
{
    sf::Event event;
    sf::Clock drawClock;

    while (_window.isOpen()) {
        while (_window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        ImGui::SFML::Update(_window, _clock.restart());

        _fbMutex.lock();
        this->draw();
        _fbMutex.unlock();
        ImGui::PopStyleVar(2);

        displayMenu();

        ImGui::SFML::Render(_window);
        _window.display();
        _fbMutex.unlock();
    }
    ImGui::SFML::Shutdown();
}

void RayTracer::Plugin::RendererPreview::draw()
{
    int i = 0;

    for (auto &pixel : _pixels) {
        int r = static_cast<int>(std::clamp(pixel.x, 0.0, 1.0) * 255.0);
        int g = static_cast<int>(std::clamp(pixel.y, 0.0, 1.0) * 255.0);
        int b = static_cast<int>(std::clamp(pixel.z, 0.0, 1.0) * 255.0);

        _texturePixel[i] = static_cast<sf::Uint8>(r);
        _texturePixel[i + 1] = static_cast<sf::Uint8>(g);
        _texturePixel[i + 2] = static_cast<sf::Uint8>(b);
        _texturePixel[i + 3] = 255;
        i += 4;
    }
    _texture.update(_texturePixel.data());

    ImGui::SetNextWindowSize(ImVec2(_width, _height));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Raytracer", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove);

    ImVec2 imageSize(_width, _height);
    ImTextureID textureID = (ImTextureID)(intptr_t)_texture.getNativeHandle();
    // flip the image upside down
    ImGui::Image(textureID, imageSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
}

void RayTracer::Plugin::RendererPreview::displayMenu()
{
    static char rawFilename[256] = {0};
    ImGui::Begin("RayTracer", nullptr, ImGuiWindowFlags_NoNavInputs);
    ImGui::Text("Time remaining: %s", secondsToTimeString());
    ImGui::Text("Save as:");
    ImGui::InputText("##Filename", rawFilename, 256);
    if (ImGui::Button("Save")) {
        _filename = rawFilename;
        if (rawFilename[_filename.size() - 1] == 'm' && rawFilename[_filename.size() - 2] == 'p' &&
        rawFilename[_filename.size() - 3] == 'p'
        && rawFilename[_filename.size() - 4] == '.') {
            writePPM(_filename);
        } else {
            writeImage(_filename);
        }
        for (int i = 0; i < 256; i++)
            rawFilename[i] = 0;
    }
    ImGui::Text("Only .png, .jpg, .bmp, .tga and .ppm are supported!");
    ImGui::End();
}

void RayTracer::Plugin::RendererPreview::writeImage(const std::string &filename)
{
    sf::Image originalImage = _texture.copyToImage();
    sf::Vector2u textureSize = _texture.getSize();
    sf::Image flippedImage;

    // Create a new image and copy the pixels in reverse order
    flippedImage.create(textureSize.x, textureSize.y);
    for (unsigned int y = 0; y < textureSize.y; y++)
    {
        for (unsigned int x = 0; x < textureSize.x; x++)
        {
            sf::Color pixel = originalImage.getPixel(x, textureSize.y - y - 1);
            flippedImage.setPixel(x, y, pixel);
        }
    }
    flippedImage.saveToFile(filename);
}

void RayTracer::Plugin::RendererPreview::writePPM(const std::string &filename)
{
    std::fstream fs(filename, std::fstream::out | std::fstream::binary);

    fs << "P6\n";
    fs << _width << " " << _height << "\n";
    fs << "255\n";
    _fbMutex.lock();
    for (auto it = _pixels.rbegin(); it != _pixels.rend(); ++it) {
      const auto& pixel = *it;
      int r = static_cast<int>(std::clamp(pixel.x, 0.0, 1.0) * 255.0);
      int g = static_cast<int>(std::clamp(pixel.y, 0.0, 1.0) * 255.0);
      int b = static_cast<int>(std::clamp(pixel.z, 0.0, 1.0) * 255.0);

      fs << static_cast<char>(r);
      fs << static_cast<char>(g);
      fs << static_cast<char>(b);
    }
    _fbMutex.unlock();
    fs.close();
}

const char *RayTracer::Plugin::RendererPreview::secondsToTimeString()
{
    int seconds = static_cast<int>(_remaining.load());
    int minutes = seconds / 60;
    int hours = minutes / 60;

    seconds %= 60;
    minutes %= 60;
    std::string timeString = std::to_string(hours) + "h " + std::to_string(minutes) + "m " + std::to_string(seconds) +
    "s";
    return timeString.c_str();
}
