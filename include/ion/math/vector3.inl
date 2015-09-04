template<typename T>
inline Vector3<T>::Vector3() : x(0), y(0), z(0) {}

template<typename T>
inline Vector3<T>::Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

template<typename T>
inline Vector3<T>::Vector3(const Vector3<T>& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }
}

template<typename T>
inline Vector3<T>::Vector3(Vector3<T>&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        y = std::move(rhs.y);
        z = std::move(rhs.z);
    }
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator=(Vector3<T>&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        y = std::move(rhs.y);
        z = std::move(rhs.z);
    }
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const T rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(const T rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const T rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
}

template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const T rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

template<typename T>
inline Vector3<T> operator+(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return Vector3<T>(lhs) += rhs;
}

template<typename T>
inline Vector3<T> operator+(const Vector3<T>& lhs, const T rhs)
{
    return Vector3<T>(lhs) += rhs;
}

template<typename T>
inline Vector3<T> operator-(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return Vector3<T>(lhs) -= rhs;
}

template<typename T>
inline Vector3<T> operator-(const Vector3<T>& lhs, const T rhs)
{
    return Vector3<T>(lhs) -= rhs;
}

template<typename T>
inline Vector3<T> operator/(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return Vector3<T>(lhs) /= rhs;
}

template<typename T>
inline Vector3<T> operator/(const Vector3<T>& lhs, const T rhs)
{
    return Vector3<T>(lhs) /= rhs;
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return Vector3<T>(lhs) *= rhs;
}

template<typename T>
inline Vector3<T> operator*(const Vector3<T>& lhs, const T rhs)
{
    return Vector3<T>(lhs) *= rhs;
}

template <typename T>
inline bool operator==(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z);
}

template <typename T>
inline bool operator!=(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return (lhs.x != rhs.x) || (lhs.y != rhs.y) || (lhs.z != rhs.z);
}

template<typename T>
inline T length(const Vector3<T>& v)
{
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

template<typename T>
inline T length_squared(const Vector3<T>& v)
{
    return std::sqrt(length(v));
}

template<typename T>
inline Vector3<T> normal(const Vector3<T>& v)
{
    return v / length(v);
}

template<typename T>
inline T dot(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

template<typename T>
inline Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs)
{
    return
    {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const Vector3<T>& v)
{
    return out << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
}
