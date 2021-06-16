#ifndef VECTORMATRIX_H
#define VECTORMATRIX_H


#define _USE_MATH_DEFINES
#include <cmath>


struct Vector3D {
    long double x,y,z;
    Vector3D(long double _x, long double _y, long double _z);
    Vector3D();

    long double abs() const;
    long double dot(const Vector3D &op1) const;
    Vector3D cross(const Vector3D &op1) const;
    long double alfa(const Vector3D &op1) const;
    Vector3D normalize() const;

    Vector3D & operator+();
    Vector3D & operator-();
    Vector3D & operator+=(const Vector3D &op1);
    Vector3D & operator-=(const Vector3D &op1);
    Vector3D & operator*=(long double k);
    Vector3D & operator/=(long double k);
};

Vector3D operator+(const Vector3D &op1, const Vector3D &op2);
Vector3D operator-(const Vector3D &op1, const Vector3D &op2);
Vector3D operator*(const Vector3D &op1, long double k);
Vector3D operator*(long double k, const Vector3D &op1);
Vector3D operator/(const Vector3D &op1, long double k);


struct Matrix3x3 {
    long double A[3][3];
    Matrix3x3();
    Matrix3x3(long double a11, long double a12, long double a13, \
              long double a21, long double a22, long double a23, \
              long double a31, long double a32, long double a33);

    Matrix3x3 & operator+();
    Matrix3x3 & operator-();
    Matrix3x3 & operator+=(const Matrix3x3 &op1);
    Matrix3x3 & operator-=(const Matrix3x3 &op1);
    Matrix3x3 & operator*=(long double k);
    Matrix3x3 & operator/=(long double k);
};

Matrix3x3 operator+(const Matrix3x3 &op1, const Matrix3x3 &op2);
Matrix3x3 operator-(const Matrix3x3 &op1, const Matrix3x3 &op2);
Matrix3x3 operator*(const Matrix3x3 &op1, long double k);
Matrix3x3 operator*(long double k, const Matrix3x3 &op1);
Matrix3x3 operator/(const Matrix3x3 &op1, long double k);
Matrix3x3 operator*(const Matrix3x3 &op1, const Matrix3x3 &op2);
Vector3D operator*(const Vector3D &op1, const Matrix3x3 &op2);
Vector3D operator*(const Matrix3x3 &op1, const Vector3D &op2);


#endif // VECTORMATRIX_H
