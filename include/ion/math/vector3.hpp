#pragma once

#include <cmath>
#include <ostream>

namespace ion { namespace math
{
template<typename T>
    class Vector3
    {
    public:
        T x;
        T y;
        T z;
    public:
        Vector3();
        Vector3(T x, T y, T z);
        Vector3(const Vector3<T>& rhs);
        Vector3(Vector3<T>&& rhs);
        Vector3<T>& operator=(const Vector3<T>& rhs);
        Vector3<T>& operator=(Vector3<T>&& rhs);
        Vector3<T>& operator+=(const Vector3<T>& rhs);
        Vector3<T>& operator+=(const T rhs);
        Vector3<T>& operator-=(const Vector3<T>& rhs);
        Vector3<T>& operator-=(const T rhs);
        Vector3<T>& operator/=(const Vector3<T>& rhs);
        Vector3<T>& operator/=(const T rhs);
        Vector3<T>& operator*=(const Vector3<T>& rhs);
        Vector3<T>& operator*=(const T rhs);
    };

    template<typename T>
    Vector3<T> operator+(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template<typename T>
    Vector3<T> operator+(const Vector3<T>& lhs, const T rhs);

    template<typename T>
    Vector3<T> operator-(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template<typename T>
    Vector3<T> operator-(const Vector3<T>& lhs, const T rhs);

    template<typename T>
    Vector3<T> operator/(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template<typename T>
    Vector3<T> operator/(const Vector3<T>& lhs, const T rhs);

    template<typename T>
    Vector3<T> operator*(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template<typename T>
    Vector3<T> operator*(const Vector3<T>& lhs, const T rhs);

    template <typename T>
    bool operator==(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template <typename T>
    bool operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template<typename T>
    T length(const Vector3<T>& v);

    template<typename T>
    T length_squared(const Vector3<T>& v);

    template<typename T>
    Vector3<T> normal(const Vector3<T>& v);

    template<typename T>
    T dot(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template<typename T>
    Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs);

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Vector3<T>& v);

    #include "vector3.inl"

    typedef Vector3<double> Vector3d;
    typedef Vector3<float> Vector3f;
    typedef Vector3<int> Vector3i;
}}
