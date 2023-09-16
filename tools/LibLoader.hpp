/*
** EPITECH PROJECT, 2023
** B-OOP-400-REN-4-1-raytracer-jovan.hillion
** File description:
** LibLoader
*/

#ifndef LIBLOADER_HPP_
#define LIBLOADER_HPP_

    #include <iostream>
    #include <dlfcn.h>
    #include <string>
    #include <functional>

namespace RayTracer {
    template <typename T>
    class LibLoader {
        public:
            LibLoader() = default;
            ~LibLoader() = default;

            static void *openModule(const std::string &filepath);
            static T *loadModule(void *module, const std::string &entryPoint);
            static void closeModule(void *module);
    };

    template <typename T>
    inline void *LibLoader<T>::openModule(const std::string &filepath)
    {
        void *library = nullptr;

        library = dlopen(filepath.c_str(), RTLD_LAZY | RTLD_NODELETE);
        if (!library)
            throw std::runtime_error("Error: " + std::string(dlerror()));
        return library;
    }

    template <typename T>
    inline void LibLoader<T>::closeModule(void *module)
    {
        try {
            if (module != nullptr)
                dlclose(module);
        } catch (const std::exception &e) {
            throw std::runtime_error("Error: " + std::string(dlerror()));
        }
    }

    template <typename T>
    inline T* LibLoader<T>::loadModule(void *library, const std::string &entryPoint)
    {
        T *(*module)() = nullptr;
        module = (T *(*)())dlsym(library, entryPoint.c_str());
        if (!module)
            throw std::runtime_error("Error: " + std::string(dlerror()));
        T *lib = (T *)(module)();
        return lib;
    }
};

#endif /* !LIBLOADER_HPP_ */
