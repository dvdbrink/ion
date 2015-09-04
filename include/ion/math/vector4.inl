template<typename T>
inline Vector4<T>::Vector4() : x(0), y(0), z(0), w(0) {}

template<typename T>
inline Vector4<T>::Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

template<typename T>
inline Vector4<T>::Vector4(const Vector4<T>& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
    }
}

template<typename T>
inline Vector4<T>::Vector4(Vector4<T>&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        y = std::move(rhs.y);
        z = std::move(rhs.z);
        w = std::move(rhs.w);
    }
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(const Vector4<T>& rhs)
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

template<typename T>
inline Vector4<T>& Vector4<T>::operator=(Vector4<T>&& rhs)
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

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(const Vector4<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator+=(const T rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator-=(const Vector4<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator-=(const T rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator/=(const Vector4<T>& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator/=(const T rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator*=(const Vector4<T>& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
}

template<typename T>
inline Vector4<T>& Vector4<T>::operator*=(const T rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

template<typename T>
inline Vector4<T> operator+(const Vector4<T>& lhs, const Vector4<T>& rhs)
{
    return Vector4<T>(lhs) += rhs;
}

template<typename T>
inline Vector4<T> operator+(const Vector4<T>& lhs, const T rhs)
{
    return Vector4<T>(lhs) += rhs;
}

template<typename T>
inline Vector4<T> operator-(const Vector4<T>& lhs, const Vector4<T>& rhs)
{
    return Vector4<T>(lhs) -= rhs;
}

template<typename T>
inline Vector4<T> operator-(const Vector4<T>& lhs, const T rhs)
{
    return Vector4<T>(lhs) -= rhs;
}

template<typename T>
inline Vector4<T> operator/(const Vector4<T>& lhs, const Vector4<T>& rhs)
{
    return Vector4<T>(lhs) /= rhs;
}

template<typename T>
inline Vector4<T> operator/(const Vector4<T>& lhs, const T rhs)
{
    return Vector4<T>(lhs) /= rhs;
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& lhs, const Vector4<T>& rhs)
{
    return Vector4<T>(lhs) *= rhs;
}

template<typename T>
inline Vector4<T> operator*(const Vector4<T>& lhs, const T rhs)
{
    return Vector4<T>(lhs) *= rhs;
}

template <typename T>
inline bool operator==(const Vector4<T>& lhs, const Vector4<T>& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z) && (lhs.w == rhs.w);
}

template <typename T>
inline bool operator!=(const Vector4<T>& lhs, const Vector4<T>& rhs)
{
    return (lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z) || (lhs.w != rhs.w);
}

template<typename T>
inline T length(const Vector4<T>& v)
{
    return v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w;
}

template<typename T>
inline T length_squared(const Vector4<T>& v)
{
    return std::sqrt(length(v));
}

template<typename T>
inline Vector4<T> normal(const Vector4<T>& v)
{
    return v / length(v);
}

template<typename T>
inline T dot(const Vector4<T>& lhs, const Vector4<T>& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z + lhs.w*rhs.w;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const Vector4<T>& v)
{
    return out << "Vector4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}
