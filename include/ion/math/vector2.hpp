#pragma once

#include <cmath>
#include <ostream>

namespace ion { namespace math
{
    template<typename T>
    class Vector2
    {
    public:
        T x;
        T y;
    public:
        Vector2();
        Vector2(T x, T y);
        Vector2(const Vector2<T>& rhs);
        Vector2(Vector2<T>&& rhs);
        Vector2<T>& operator=(const Vector2<T>& rhs);
        Vector2<T>& operator=(Vector2<T>&& rhs);
        Vector2<T>& operator+=(const Vector2<T>& rhs);
        Vector2<T>& operator+=(const T rhs);
        Vector2<T>& operator-=(const Vector2<T>& rhs);
        Vector2<T>& operator-=(const T rhs);
        Vector2<T>& operator/=(const Vector2<T>& rhs);
        Vector2<T>& operator/=(const T rhs);
        Vector2<T>& operator*=(const Vector2<T>& rhs);
        Vector2<T>& operator*=(const T rhs);
    };

    template<typename T>
    Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs);

    template<typename T>
    Vector2<T> operator+(const Vector2<T>& lhs, const T rhs);

    template<typename T>
    Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs);

    template<typename T>
    Vector2<T> operator-(const Vector2<T>& lhs, const T rhs);

    template<typename T>
    Vector2<T> operator/(const Vector2<T>& lhs, const Vector2<T>& rhs);

    template<typename T>
    Vector2<T> operator/(const Vector2<T>& lhs, const T rhs);

    template<typename T>
    Vector2<T> operator*(const Vector2<T>& lhs, const Vector2<T>& rhs);

    template<typename T>
    Vector2<T> operator*(const Vector2<T>& lhs, const T rhs);

    template <typename T>
    bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs);

    template <typename T>
    bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs);

    template<typename T>
    T length(const Vector2<T>& v);

    template<typename T>
    T length_squared(const Vector2<T>& v);

    template<typename T>
    Vector2<T> normal(const Vector2<T>& v);

    template<typename T>
    T dot(const Vector2<T>& lhs, const Vector2<T>& rhs);

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vector2<T>& v);

    #include "vector2.inl"

    typedef Vector2<double> Vector2d;
    typedef Vector2<float> Vector2f;
    typedef Vector2<int> Vector2i;
}}
