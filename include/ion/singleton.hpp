#pragma once

#include <memory>

namespace ion
{
    template<typename T>
    class Singleton
    {
    public:
        static T& get() {
            if (instance.get() == nullptr)
            {
                instance = std::make_shared<T>();
            }
            return *instance;
        }

    private:
        static std::shared_ptr<T> instance;

    private:
        Singleton() {}
        ~Singleton() {}
    };

    template<typename T>
    std::shared_ptr<T> Singleton<T>::instance = nullptr;
}
