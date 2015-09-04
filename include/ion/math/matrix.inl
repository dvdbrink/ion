template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>::Matrix()
{
    for (unsigned int i = 0; i < R; i++)
    {
        for (unsigned int j = 0; j < C; j++)
        {
            m[i][j] = (T)((i == j) ? 1 : 0);
        }
    }
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>::Matrix(std::initializer_list<T> list)
{
    assert(list.size() == R*C);
    auto iterator = begin(list);
    for (unsigned int i = 0; i < R; i++)
    {
        for (unsigned int j = 0; j < C; j++)
        {
            m[i][j] = *(iterator++);
        }
    }
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>::Matrix(const Matrix<T, R, C>& rhs)
{
    if (this != &rhs)
    {
        m = rhs.m;
    }
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>::Matrix(Matrix<T, R, C>&& rhs)
{
    if (this != &rhs)
    {
        m = std::move(rhs.m);
    }
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>& Matrix<T, R, C>::operator=(const Matrix<T, R, C>& rhs)
{
    if (this != &rhs)
    {
        m = rhs.m;
    }
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>& Matrix<T, R, C>::operator=(Matrix<T, R, C>&& rhs)
{
    if (this != &rhs)
    {
        m = std::move(rhs.m);
    }
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>& Matrix<T, R, C>::operator+=(const Matrix<T, R, C>& rhs)
{
    for (unsigned int r = 0; r < R; r++)
    {
        for (unsigned int c = 0; c < C; c++)
        {
            m[r][c] += rhs[r][c];
        }
    }
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>& Matrix<T, R, C>::operator-=(const Matrix<T, R, C>& rhs)
{
    for (unsigned int r = 0; r < R; r++)
    {
        for (unsigned int c = 0; c < C; c++)
        {
            m[r][c] -= rhs[r][c];
        }
    }
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>& Matrix<T, R, C>::operator*=(const Matrix<T, R, C>& rhs)
{
    assert(R == C);
    Matrix<T, R, C> out;
    for (unsigned int i = 0; i < R; i++)
    {
        for (unsigned int j = 0; j < C; j++)
        {
            out[i][j] = (T) 0;
            for (unsigned int k = 0; k < C; k++)
            {
                out[i][j] += m[i][k] * rhs[k][j];
            }
        }
    }
    *this = out;
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C>& Matrix<T, R, C>::operator*=(const T rhs)
{
    for (unsigned int i = 0; i < R; i++)
    {
        for (unsigned int j = 0; j < C; j++)
        {
            m[i][j] *= rhs;
        }
    }
    return *this;
}

template<typename T, std::size_t R, std::size_t C>
inline std::array<T, C>& Matrix<T, R, C>::operator[](const unsigned int i)
{
    return m[i];
}

template<typename T, std::size_t R, std::size_t C>
inline const std::array<T, C>& Matrix<T, R, C>::operator[](const unsigned int i) const
{
    return m[i];
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C> operator+(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
{
    return Matrix<T, R, C>(lhs) += rhs;
}

template<typename T, std::size_t R, std::size_t C>
inline Matrix<T, R, C> operator-(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
{
    return Matrix<T, R, C>(lhs) -= rhs;
}

template<typename T, size_t R, size_t C>
inline Matrix<T, R, C> operator*(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
{
    return Matrix<T, R, C>(lhs) *= rhs;
}

template<typename T, size_t R, size_t C>
inline Matrix<T, R, C> operator*(const Matrix<T, R, C>& lhs, const T rhs)
{
    return Matrix<T, R, C>(lhs) *= rhs;
}

template<typename T, size_t R, size_t C, size_t N>
inline Vector3<T> operator*(const Matrix<T, R, C>& lhs, const Vector3<T>& rhs)
{
    return Matrix<T, R, C>(lhs) *= rhs;
}

template<typename T, size_t R, size_t C>
inline bool operator==(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
{
    for (unsigned int r = 0; r < R; r++)
    {
        for (unsigned int c = 0; c < C; c++)
        {
            if (lhs[r][c] != rhs[r][c])
            {
                return false;
            }
        }
    }
    return true;
}

template<typename T, size_t R, size_t C>
inline bool operator!=(const Matrix<T, R, C>& lhs, const Matrix<T, R, C>& rhs)
{
    for (unsigned int r = 0; r < R; r++)
    {
        for (unsigned int c = 0; c < C; c++)
        {
            if (lhs[r][c] == rhs[r][c])
            {
                return false;
            }
        }
    }
    return true;
}

template<typename T, size_t R, size_t C>
inline std::ostream& operator<<(std::ostream& out, const Matrix<T, R, C>& rhs)
{
    for (unsigned int i = 0; i < R; i++)
    {
        for (unsigned int j = 0; j < C; j++)
        {
            out << rhs[i][j];
            if (j < C-1)
            {
                out << ", ";
            }
        }
        if (i < R-1)
        {
            out << "\n";
        }
    }
    return out;
}

template<typename T, size_t R, size_t C>
inline Matrix<T, R, C> transpose(const Matrix<T, R, C>& in)
{
    assert(R == C);
    Matrix<T, R, C> out;
    for (unsigned int i = 0; i < R; i++)
    {
        for (unsigned int j = 0; j < C; j++)
        {
            out[j][i] = in[i][j];
        }
    }
    return out;
}

template<typename T>
inline T determinant(const Matrix<T, 2, 2>& in)
{
    return in[0][0] * in[1][1] - in[0][1] * in[1][0];
}

template<typename T>
inline T determinant(const Matrix<T, 3, 3>& in)
{
    return in[0][0] * (in[1][1] * in[2][2] - in[2][1] * in[1][2]) +
           in[0][1] * (in[2][0] * in[1][2] - in[1][0] * in[2][2]) +
           in[0][2] * (in[1][0] * in[2][1] - in[2][0] * in[1][1]);
}

template<typename T>
inline T determinant(const Matrix<T, 4, 4>& in)
{
    return in[3][0]*in[2][1]*in[1][2]*in[0][3] - in[2][0]*in[3][1]*in[1][2]*in[0][3] - in[3][0]*in[1][1]*in[2][2]*in[0][3] + in[1][0]*in[3][1]*in[2][2]*in[0][3] +
           in[2][0]*in[1][1]*in[3][2]*in[0][3] - in[1][0]*in[2][1]*in[3][2]*in[0][3] - in[3][0]*in[2][1]*in[0][2]*in[1][3] + in[2][0]*in[3][1]*in[0][2]*in[1][3] +
           in[3][0]*in[0][1]*in[2][2]*in[1][3] - in[0][0]*in[3][1]*in[2][2]*in[1][3] - in[2][0]*in[0][1]*in[3][2]*in[1][3] + in[0][0]*in[2][1]*in[3][2]*in[1][3] +
           in[3][0]*in[1][1]*in[0][2]*in[2][3] - in[1][0]*in[3][1]*in[0][2]*in[2][3] - in[3][0]*in[0][1]*in[1][2]*in[2][3] + in[0][0]*in[3][1]*in[1][2]*in[2][3] +
           in[1][0]*in[0][1]*in[3][2]*in[2][3] - in[0][0]*in[1][1]*in[3][2]*in[2][3] - in[2][0]*in[1][1]*in[0][2]*in[3][3] + in[1][0]*in[2][1]*in[0][2]*in[3][3] +
           in[2][0]*in[0][1]*in[1][2]*in[3][3] - in[0][0]*in[2][1]*in[1][2]*in[3][3] - in[1][0]*in[0][1]*in[2][2]*in[3][3] + in[0][0]*in[1][1]*in[2][2]*in[3][3];
}

template<typename T>
inline Matrix<T, 2, 2> adjugate(const Matrix<T, 2, 2>& in)
{
    return {in[1][1], -in[0][1], -in[1][0], in[0][0]};
}

template<typename T>
inline Matrix<T, 3, 3> adjugate(const Matrix<T, 3, 3>& in)
{
    Matrix<T, 3, 3> out;

    out[0][0] = in[1][1] * in[2][2] - in[1][2] * in[2][1];
    out[1][0] = in[0][2] * in[2][1] - in[0][1] * in[2][2];
    out[2][0] = in[0][1] * in[1][2] - in[0][2] * in[1][1];

    out[0][1] = in[1][2] * in[2][0] - in[1][0] * in[2][2];
    out[1][1] = in[0][0] * in[2][2] - in[0][2] * in[2][0];
    out[2][1] = in[0][2] * in[1][0] - in[0][0] * in[1][2];

    out[0][2] = in[1][0] * in[2][1] - in[1][1] * in[2][0];
    out[1][2] = in[0][1] * in[2][0] - in[0][0] * in[2][1];
    out[2][2] = in[0][0] * in[1][1] - in[0][1] * in[1][0];

    return out;
}

template<typename T>
inline Matrix<T, 4, 4> adjugate(const Matrix<T, 4, 4>& in)
{
    Matrix<T, 4, 4> out;

    out[0][0] = in[1][1]*in[2][2]*in[3][3] + in[2][1]*in[3][2]*in[1][3] + in[3][1]*in[1][2]*in[2][3] - in[1][1]*in[3][2]*in[2][3] - in[2][1]*in[1][2]*in[3][3] - in[3][1]*in[2][2]*in[1][3];
    out[1][0] = in[0][1]*in[3][2]*in[2][3] + in[2][1]*in[0][2]*in[3][3] + in[3][1]*in[2][2]*in[0][3] - in[0][1]*in[2][2]*in[3][3] - in[2][1]*in[3][2]*in[0][3] - in[3][1]*in[0][2]*in[2][3];
    out[2][0] = in[0][1]*in[1][2]*in[3][3] + in[1][1]*in[3][2]*in[0][3] + in[3][1]*in[0][2]*in[1][3] - in[0][1]*in[3][2]*in[1][3] - in[1][1]*in[0][2]*in[3][3] - in[3][1]*in[1][2]*in[0][3];
    out[3][0] = in[0][1]*in[2][2]*in[1][3] + in[1][1]*in[0][2]*in[2][3] + in[2][1]*in[1][2]*in[0][3] - in[0][1]*in[1][2]*in[2][3] - in[1][1]*in[2][2]*in[0][3] - in[2][1]*in[0][2]*in[1][3];

    out[0][1] = in[1][0]*in[3][2]*in[2][3] + in[2][0]*in[1][2]*in[3][3] + in[3][0]*in[2][2]*in[1][3] - in[1][0]*in[2][2]*in[3][3] - in[2][0]*in[3][2]*in[1][3] - in[3][0]*in[1][2]*in[2][3];
    out[1][1] = in[0][0]*in[2][2]*in[3][3] + in[2][0]*in[3][2]*in[0][3] + in[3][0]*in[0][2]*in[2][3] - in[0][0]*in[3][2]*in[2][3] - in[2][0]*in[0][2]*in[3][3] - in[3][0]*in[2][2]*in[0][3];
    out[2][1] = in[0][0]*in[3][2]*in[1][3] + in[1][0]*in[0][2]*in[3][3] + in[3][0]*in[1][2]*in[0][3] - in[0][0]*in[1][2]*in[3][3] - in[1][0]*in[3][2]*in[0][3] - in[3][0]*in[0][2]*in[1][3];
    out[3][1] = in[0][0]*in[1][2]*in[2][3] + in[1][0]*in[2][2]*in[0][3] + in[2][0]*in[0][2]*in[1][3] - in[0][0]*in[2][2]*in[1][3] - in[1][0]*in[0][2]*in[2][3] - in[2][0]*in[1][2]*in[0][3];

    out[0][2] = in[1][0]*in[2][1]*in[3][3] + in[2][0]*in[3][1]*in[1][3] + in[3][0]*in[1][1]*in[2][3] - in[1][0]*in[3][1]*in[2][3] - in[2][0]*in[1][1]*in[3][3] - in[3][0]*in[2][1]*in[1][3];
    out[1][2] = in[0][0]*in[3][1]*in[2][3] + in[2][0]*in[0][1]*in[3][3] + in[3][0]*in[2][1]*in[0][3] - in[0][0]*in[2][1]*in[3][3] - in[2][0]*in[3][1]*in[0][3] - in[3][0]*in[0][1]*in[2][3];
    out[2][2] = in[0][0]*in[1][1]*in[3][3] + in[1][0]*in[3][1]*in[0][3] + in[3][0]*in[0][1]*in[1][3] - in[0][0]*in[3][1]*in[1][3] - in[1][0]*in[0][1]*in[3][3] - in[3][0]*in[1][1]*in[0][3];
    out[3][2] = in[0][0]*in[2][1]*in[1][3] + in[1][0]*in[0][1]*in[2][3] + in[2][0]*in[1][1]*in[0][3] - in[0][0]*in[1][1]*in[2][3] - in[1][0]*in[2][1]*in[0][3] - in[2][0]*in[0][1]*in[1][3];

    out[0][3] = in[1][0]*in[3][1]*in[2][2] + in[2][0]*in[1][1]*in[3][2] + in[3][0]*in[2][1]*in[1][2] - in[1][0]*in[2][1]*in[3][2] - in[2][0]*in[3][1]*in[1][2] - in[3][0]*in[1][1]*in[2][2];
    out[1][3] = in[0][0]*in[2][1]*in[3][2] + in[2][0]*in[3][1]*in[0][2] + in[3][0]*in[0][1]*in[2][2] - in[0][0]*in[3][1]*in[2][2] - in[2][0]*in[0][1]*in[3][2] - in[3][0]*in[2][1]*in[0][2];
    out[2][3] = in[0][0]*in[3][1]*in[1][2] + in[1][0]*in[0][1]*in[3][2] + in[3][0]*in[1][1]*in[0][2] - in[0][0]*in[1][1]*in[3][2] - in[1][0]*in[3][1]*in[0][2] - in[3][0]*in[0][1]*in[1][2];
    out[3][3] = in[0][0]*in[1][1]*in[2][2] + in[1][0]*in[2][1]*in[0][2] + in[2][0]*in[0][1]*in[1][2] - in[0][0]*in[2][1]*in[1][2] - in[1][0]*in[0][1]*in[2][2] - in[2][0]*in[1][1]*in[0][2];

    return out;
}

template<typename T, size_t R, size_t C>
inline Matrix<T, R, C> inverse(const Matrix<T, R, C>& in)
{
    assert(R == C);
    float d = determinant(in);
    assert(d != 0);
    return adjugate(in) * (1.0f / d);
}

template<typename T>
inline Matrix<T, 4, 4> translate(const Matrix<T, 4, 4>& in, const Vector3<T>& translation)
{
    Matrix<T, 4, 4> out(in);
    out[3][0] = translation.x;
    out[3][1] = translation.y;
    out[3][2] = translation.z;
    return out;
}

template<typename T>
inline Matrix<T, 4, 4> scale(const Matrix<T, 4, 4>& in, const Vector3<T>& scalar)
{
    Matrix<T, 4, 4> out(in);
    out[0][0] *= scalar.x;
    out[1][1] *= scalar.y;
    out[2][2] *= scalar.z;
    return out;
}

template<typename T, typename U>
inline Vector3<T> project(const Vector3<T>& point, const Matrix<T, 4, 4>& projection, const Matrix<T, 4, 4>& view, const Vector4<U>& viewport)
{
    Vector4<T> tmp = Vector4<T>{point.x, point.y, point.z, T(1)};
    tmp = view * tmp;
    tmp = projection * tmp;

    tmp /= tmp.w;
    tmp = tmp * T(0.5) + T(0.5);
    tmp.x = tmp.x * T(viewport.z) + T(viewport.x);
    tmp.y = tmp.y * T(viewport.w) + T(viewport.y);

    return Vector3<T>{tmp.x, tmp.y, tmp.z};
}

template<typename T, typename U>
inline Vector3<T> unproject(const Vector3<T>& point, const Matrix<T, 4, 4>& projection, const Matrix<T, 4, 4>& view, const Vector4<U>& viewport)
{
    Matrix<T, 4, 4> inverse = inverse(projection * view);

    Vector4<T> tmp = Vector4<T>{point.x, point.y, point.z, T(1)};
    tmp[0] = (tmp[0] - T(viewport.x) / T(viewport.z));
    tmp[1] = (tmp[1] - T(viewport.y) / T(viewport.w));
    tmp = tmp * T(2) - T(1);

    Vector4<T> obj = inverse * tmp;
    obj /= obj.w;

    return Vector3<T>{obj.x, obj.y, obj.z};
}

template<typename T>
inline Matrix<T, 4, 4> perspective(const T fieldOfView, const T aspectRatio, const T nearPlane, const T farPlane)
{
    T yScale = (T)(1.0f / std::tan((fieldOfView / 2.0f) * (3.14159265f / 180.0f)));
    T xScale = yScale / aspectRatio;
    T frustumLength = farPlane - nearPlane;

    Matrix<T, 4, 4> out;

    out[0][0] = xScale;
    out[1][1] = yScale;
    out[2][2] = -((farPlane + nearPlane) / frustumLength);
    out[2][3] = -1;
    out[3][2] = -((2 * nearPlane * farPlane) / frustumLength);

    return out;
}

template<typename T>
inline Matrix<T, 4, 4> ortho(const T left, const T right, const T bottom, const T top, const T zNear, const T zFar)
{
    Matrix<T, 4, 4> out;

    out[0][0] = T(2) / (right - left);
    out[1][1] = T(2) / (top - bottom);
    out[2][2] = -T(2) / (zFar - zNear);
    out[3][0] = -(right + left) / (right - left);
    out[3][1] = -(top + bottom) / (top - bottom);
    out[3][2] = -(zFar + zNear) / (zFar - zNear);

    return out;
}

template<typename T>
inline Matrix<T, 4, 4> look_at(const Vector3<T>& position, const Vector3<T>& target, const Vector3<T>& up)
{
    Vector3<T> zAxis = normal(position - target);
    Vector3<T> xAxis = normal(cross(up, zAxis));
    Vector3<T> yAxis = cross(zAxis, xAxis);

    Matrix<T, 4, 4> out;

    out[0][0] = xAxis.x;
    out[1][0] = xAxis.y;
    out[2][0] = xAxis.z;

    out[0][1] = yAxis.x;
    out[1][1] = yAxis.y;
    out[2][1] = yAxis.z;

    out[0][2] = zAxis.x;
    out[1][2] = zAxis.y;
    out[2][2] = zAxis.z;

    out[3][0] = -dot(xAxis, position);
    out[3][1] = -dot(yAxis, position);
    out[3][2] = -dot(zAxis, position);

    return out;
}
