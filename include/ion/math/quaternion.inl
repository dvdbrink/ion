inline Quaternion::Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

inline Quaternion::Quaternion(const float x, const float y, const float z, const float w) :
    x(x), y(y), z(z), w(w) {}

inline Quaternion::Quaternion(const Quaternion& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
    }
}

inline Quaternion::Quaternion(Quaternion&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        y = std::move(rhs.y);
        z = std::move(rhs.z);
        w = std::move(rhs.w);
    }
}

inline Quaternion& Quaternion::operator=(const Quaternion& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
    }
    return *this;
}

inline Quaternion& Quaternion::operator=(Quaternion&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        y = std::move(rhs.y);
        z = std::move(rhs.z);
        w = std::move(rhs.w);
    }
    return *this;
}

inline math::Matrix4f Quaternion::getMatrix()
{
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    return
    {
        1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
        2.0f * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx), 0.0f,
        2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
{
    return Quaternion
    (
        lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
        lhs.w * rhs.w - lhs.x * rhs.w - lhs.y * rhs.y - lhs.z * rhs.z
    );
}

inline Vector3f operator*(const Quaternion& q, const Vector3f& v)
{
    Vector3f uv, uuv;
    Vector3f qvec{q.x, q.y, q.z};
    uv = cross(qvec, v);
    uuv = cross(qvec, uv);
    uv *= (2.0f * q.w);
    uuv *= 2.0f;
    return v + uv + uuv;
}

inline Quaternion operator/(const Quaternion& lhs, const float rhs)
{
    return Quaternion(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
}

inline float dot(const Quaternion& lhs, const Quaternion& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

inline Vector3f operator*(const Vector3f& v, const Quaternion& q)
{
    return (Quaternion(-q.x, -q.y, -q.z, q.w) / dot(q, q)) * v;
}

inline Quaternion rotate(const Quaternion& in, const float angle, const Vector3f& unit)
{
    float a = radians(angle);
    float s = std::sin(a*0.5f);
    float c = std::cos(a*0.5f);
    return in * Quaternion(unit.x*s, unit.y*s, unit.z*s, c);
}

inline std::ostream& operator<<(std::ostream& out, const Quaternion& rhs)
{
    return out << "Quaternion(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
}
