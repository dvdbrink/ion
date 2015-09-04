#pragma once

#include <ion/math/vector3.hpp>
#include <ion/math/vector4.hpp>

#include <array>
#include <cassert>
#include <cmath>
#include <ostream>

namespace ion { namespace math
{
    template<typename T, size_t R, size_t C>
    class Matrix
    {
    public:
        Matrix();
        Matrix(std::initializer_list<T> list);
        Matrix(const Matrix<T, R, C>& rhs);
        Matrix(Matrix<T, R, C>&& rhs);
        Matrix<T, R, C>& operator=(const Matrix<T, R, C>& rhs);
        Matrix<T, R, C>& operator=(Matrix<T, R, C>&& rhs);
        Matrix<T, R, C>& operator+=(const Matrix<T, R, C>& rhs);
        Matrix<T, R, C>& operator-=(const Matrix<T, R, C>& rhs);
        Matrix<T, R, C>& operator*=(const Matrix<T, R, C>& rhs);
        Matrix<T, R, C>& operator*=(const T rhs);
        std::array<T, C>& operator[](const unsigned int i);
        const std::array<T, C>& operator[](const unsigned int i) const;
    private:
        std::array<std::array<T, C>, R> m;
    };

    template<typename T, std::size_t R, std::size_t C>
    Matrix<T, R, C> operator+(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs);

    template<typename T, std::size_t R, std::size_t C>
    Matrix<T, R, C> operator-(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs);

    template<typename T, size_t R, size_t C>
    Matrix<T, R, C> operator*(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs);

    template<typename T, size_t R, size_t C>
    Matrix<T, R, C> operator*(const Matrix<T, R, C>& lhs, const T rhs);

    template<typename T, size_t R, size_t C>
    bool operator==(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs);

    template<typename T, size_t R, size_t C>
    bool operator!=(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs);

    template<typename T, size_t R, size_t C>
    std::ostream& operator<<(std::ostream& out, const Matrix<T, R, C>& rhs);

    template<typename T, size_t R, size_t C>
    Matrix<T, R, C> transpose(const Matrix<T, R, C>& in);

    template<typename T>
    T determinant(const Matrix<T, 2, 2>& in);

    template<typename T>
    T determinant(const Matrix<T, 3, 3>& in);

    template<typename T>
    T determinant(const Matrix<T, 4, 4>& in);

    template<typename T>
    Matrix<T, 2, 2> adjugate(const Matrix<T, 2, 2>& in);

    template<typename T>
    Matrix<T, 3, 3> adjugate(const Matrix<T, 3, 3>& in);

    template<typename T>
    Matrix<T, 4, 4> adjugate(const Matrix<T, 4, 4>& in);

    template<typename T, size_t R, size_t C>
    Matrix<T, R, C> inverse(const Matrix<T, R, C>& in);

    template<typename T, size_t N>
    Matrix<T, 4, 4> translate(const Matrix<T, 4, 4>& in, const Vector3<T>& translation);

    template<typename T, size_t N>
    Matrix<T, 4, 4> scale(const Matrix<T, 4, 4>& in, const Vector3<T>& scalar);

    template<typename T, typename U>
    Vector3<T> project(const Vector3<T>& point, const Matrix<T, 4, 4>& projection, const Matrix<T, 4, 4>& view, const Vector4<U>& viewport);

    template<typename T, typename U>
    Vector3<T> unproject(const Vector3<T>& point, const Matrix<T, 4, 4>& projection, const Matrix<T, 4, 4>& view, const Vector4<U>& viewport);

    template<typename T>
    Matrix<T, 4, 4> perspective(const T fieldOfView, const T aspectRatio, const T nearPlane, const T farPlane);

    template<typename T>
    Matrix<T, 4, 4> ortho(const T left, const T right, const T bottom, const T top, const T near, const T far);

    template<typename T, size_t N>
    Matrix<T, 4, 4> look_at(const Vector3<T>& position, const Vector3<T>& target, const Vector3<T>& up);

    #include "matrix.inl"

    typedef Matrix<double, 2, 2> Matrix2d;
    typedef Matrix<double, 3, 3> Matrix3d;
    typedef Matrix<double, 2, 2> Matrix4d;

    typedef Matrix<float, 2, 2> Matrix2f;
    typedef Matrix<float, 3, 3> Matrix3f;
    typedef Matrix<float, 4, 4> Matrix4f;

    typedef Matrix<int, 2, 2> Matrix2i;
    typedef Matrix<int, 3, 3> Matrix3i;
    typedef Matrix<int, 4, 4> Matrix4i;
}}
