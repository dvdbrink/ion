template<typename T>
inline Vector2<T>::Vector2() : x(0), y(0) {}

template<typename T>
inline Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template<typename T>
inline Vector2<T>::Vector2(const Vector2<T>& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }
}

template<typename T>
inline Vector2<T>::Vector2(Vector2<T>&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        y = std::move(rhs.y);
    }
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& rhs)
{
    if (this != &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    }
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(Vector2<T>&& rhs)
{
    if (this != &rhs)
    {
        x = std::move(rhs.x);
        y = std::move(rhs.y);
    }
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(const T rhs)
{
    x += rhs;
    y += rhs;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(const T rhs)
{
    x -= rhs;
    y -= rhs;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& rhs)
{
    x /= rhs.x;
    y /= rhs.y;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(const T rhs)
{
    x /= rhs;
    y /= rhs;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& rhs)
{
    x *= rhs.x;
    y *= rhs.y;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(const T rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

template<typename T>
inline Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return Vector2<T>(lhs) += rhs;
}

template<typename T>
inline Vector2<T> operator+(const Vector2<T>& lhs, const T rhs)
{
    return Vector2<T>(lhs) += rhs;
}

template<typename T>
inline Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return Vector2<T>(lhs) -= rhs;
}

template<typename T>
inline Vector2<T> operator-(const Vector2<T>& lhs, const T rhs)
{
    return Vector2<T>(lhs) -= rhs;
}

template<typename T>
inline Vector2<T> operator/(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return Vector2<T>(lhs) /= rhs;
}

template<typename T>
inline Vector2<T> operator/(const Vector2<T>& lhs, const T rhs)
{
    return Vector2<T>(lhs) /= rhs;
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return Vector2<T>(lhs) *= rhs;
}

template<typename T>
inline Vector2<T> operator*(const Vector2<T>& lhs, const T rhs)
{
    return Vector2<T>(lhs) *= rhs;
}

template <typename T>
inline bool operator==(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

template <typename T>
inline bool operator!=(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}

template<typename T>
T length(const Vector2<T>& v)
{
    return v.x*v.x + v.y*v.y;
}

template<typename T>
inline T length_squared(const Vector2<T>& v)
{
    return std::sqrt(length(v));
}

template<typename T>
inline Vector2<T> normal(const Vector2<T>& v)
{
    return v / length(v);
}

template<typename T>
inline T dot(const Vector2<T>& lhs, const Vector2<T>& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

template<typename T>
inline std::ostream& operator<<(std::ostream& out, const Vector2<T>& v)
{
    return out << "Vector2(" << v.x << ", " << v.y << ")";
}
