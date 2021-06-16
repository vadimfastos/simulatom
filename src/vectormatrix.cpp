#include "vectormatrix.h"


Vector3D::Vector3D(long double _x, long double _y, long double _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}


Vector3D::Vector3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}


long double Vector3D::abs() const {
    return sqrt(x*x + y*y + z*z);
}


long double Vector3D::dot(const Vector3D &op1) const {
    return x*op1.x + y*op1.y + z*op1.z;
}


Vector3D Vector3D::cross(const Vector3D &op1) const {
    return Vector3D(y*op1.z-z*op1.y,z*op1.x-x*op1.z,x*op1.y-y*op1.x);
}


long double Vector3D::alfa(const Vector3D &op1) const {
    // a*b = abs(a)*abs(b)*cos(alfa)
    // cos(alfa) = a*b/(abs(a)*abs(b))
    long double cosa = dot(op1) / (abs() * op1.abs());
    return acos(cosa);
}


Vector3D Vector3D::normalize() const {
    long double len = sqrt(x*x + y*y + z*z);
    return Vector3D(x/len, y/len, z/len);
}


Vector3D & Vector3D::operator+() {
    return *this;
}


Vector3D & Vector3D::operator-() {
    x = -x; y = -y; z = -z;
    return *this;
}


Vector3D & Vector3D::operator+=(const Vector3D &op1) {
    x += op1.x;
    y += op1.y;
    z += op1.z;
    return *this;
}


Vector3D & Vector3D::operator-=(const Vector3D &op1) {
    x -= op1.x;
    y -= op1.y;
    z -= op1.z;
    return *this;
}


Vector3D & Vector3D::operator*=(long double k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}


Vector3D & Vector3D::operator/=(long double k) {
    x /= k;
    y /= k;
    z /= k;
    return *this;
}


Vector3D operator+(const Vector3D &op1, const Vector3D &op2) {
    return Vector3D(op1.x+op2.x, op1.y+op2.y, op1.z+op2.z);
}


Vector3D operator-(const Vector3D &op1, const Vector3D &op2) {
    return Vector3D(op1.x-op2.x, op1.y-op2.y, op1.z-op2.z);
}


Vector3D operator*(const Vector3D &op1, long double k) {
    return Vector3D(op1.x*k, op1.y*k, op1.z*k);
}


Vector3D operator*(long double k, const Vector3D &op1) {
    return Vector3D(op1.x*k, op1.y*k, op1.z*k);
}


Vector3D operator/(const Vector3D &op1, long double k) {
    return Vector3D(op1.x/k, op1.y/k, op1.z/k);
}



Matrix3x3::Matrix3x3() {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            A[i][j] = 0;
}


Matrix3x3::Matrix3x3(long double a11, long double a12, long double a13, \
          long double a21, long double a22, long double a23, \
          long double a31, long double a32, long double a33) {
    A[0][0] = a11;
    A[0][1] = a12;
    A[0][2] = a13;
    A[1][0] = a21;
    A[1][1] = a22;
    A[1][2] = a23;
    A[2][0] = a31;
    A[2][1] = a32;
    A[2][2] = a33;
}


Matrix3x3 & Matrix3x3::operator+() {
    return *this;
}


Matrix3x3 & Matrix3x3::operator-() {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            A[i][j] = -A[i][j];
    return *this;
}


Matrix3x3 & Matrix3x3::operator+=(const Matrix3x3 &op1) {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            A[i][j] += op1.A[i][j];
    return *this;
}


Matrix3x3 & Matrix3x3::operator-=(const Matrix3x3 &op1) {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            A[i][j] -= op1.A[i][j];
    return *this;
}


Matrix3x3 & Matrix3x3::operator*=(long double k) {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            A[i][j] *= k;
    return *this;
}


Matrix3x3 & Matrix3x3::operator/=(long double k) {
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            A[i][j] /= k;
    return *this;
}


Matrix3x3 operator+(const Matrix3x3 &op1, const Matrix3x3 &op2) {
    Matrix3x3 r;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            r.A[i][j] = op1.A[i][j] + op2.A[i][j];
    return r;
}


Matrix3x3 operator-(const Matrix3x3 &op1, const Matrix3x3 &op2) {
    Matrix3x3 r;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            r.A[i][j] = op1.A[i][j] - op2.A[i][j];
    return r;
}


Matrix3x3 operator*(const Matrix3x3 &op1, long double k) {
    Matrix3x3 r;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            r.A[i][j] = op1.A[i][j] * k;
    return r;
}


Matrix3x3 operator*(long double k, const Matrix3x3 &op1) {
    Matrix3x3 r;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            r.A[i][j] = op1.A[i][j] * k;
    return r;
}


Matrix3x3 operator/(const Matrix3x3 &op1, long double k) {
    Matrix3x3 r;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            r.A[i][j] = op1.A[i][j] / k;
    return r;
}


Matrix3x3 operator*(const Matrix3x3 &op1, const Matrix3x3 &op2) {
    Matrix3x3 res;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            for (int k=0; k<3; k++)
                res.A[i][j] += op1.A[i][k] * op2.A[k][j];
    return res;
}


Vector3D operator*(const Vector3D &op1, const Matrix3x3 &op2) {
    long double r[3], b[3];
    r[0] = 0; r[1] = 0; r[2] = 0;
    b[0] = op1.x; b[1] = op1.y; b[2] = op1.z;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            r[i] += b[j] * op2.A[j][i];
    return Vector3D(r[0], r[1], r[2]);
}


Vector3D operator*(const Matrix3x3 &op1, const Vector3D &op2) {
    long double res[3] = {0, 0, 0};
    long double b[3] = {op2.x, op2.y, op2.z};
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            res[i] += op1.A[i][j] * b[j];
    return Vector3D(res[0], res[1], res[2]);
}
