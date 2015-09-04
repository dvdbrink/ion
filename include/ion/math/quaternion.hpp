#pragma once

#include <ion/math/common.hpp>
#include <ion/math/matrix.hpp>
#include <ion/math/vector3.hpp>

#include <ostream>

namespace ion { namespace math
{
    class Quaternion
    {
    public:
        float x;
        float y;
        float z;
        float w;
    public:
        Quaternion();
        Quaternion(const float x, const float y, const float z, const float w);
        Quaternion(const Quaternion& rhs);
        Quaternion(Quaternion&& rhs);
        Quaternion& operator=(const Quaternion& rhs);
        Quaternion& operator=(Quaternion&& rhs);
        math::Matrix4f getMatrix();
    };

    Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);

    Vector3f operator*(const Quaternion& q, const Vector3f& v);

    Quaternion operator/(const Quaternion& lhs, const float rhs);

    float dot(const Quaternion& lhs, const Quaternion& rhs);

    Vector3f operator*(const Vector3f& v, const Quaternion& q);

    Quaternion rotate(const Quaternion& in, const float angle, const Vector3f& unit);

    std::ostream& operator<<(std::ostream& out, const Quaternion& rhs);

    #include "quaternion.inl"
}}
