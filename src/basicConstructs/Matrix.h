#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include "src/basicConstructs/Tuple.h"
#include <exception>
#include <math.h>

class Ray;

class UnInvertible: public std::exception {
    public:
    virtual const char* what() const throw() {
        return "Matrix is not invertible - determinant too small";
    }
};

class Vec;
class Point;

class Matrix {
    protected:
    float elems[16];
    public:
    Matrix(float initVal);
    Matrix(float* elems);
    Matrix(const Matrix& other);
    const Matrix& operator=(const Matrix& other);
    float getElem(int row, int col) const;
    Vec operator*(const Vec& vec) const;
    Point operator*(const Point& point) const;
    Matrix operator*(const Matrix& other) const;
    Matrix& transpose();
    Matrix getInverse() const;
};

class IdentityMat : public Matrix {
    public:
    IdentityMat();
};

class TranslationMat : public Matrix {
    public:
    TranslationMat(float x, float y, float z);
};

class ScalingMat : public Matrix {
    public:
    ScalingMat(float x, float y, float z);
};

class XRotation : public Matrix {
    public:
    XRotation(float angle);
};

class YRotation : public Matrix {
    public:
    YRotation(float angle);
};

class ZRotation : public Matrix {
    public:
    ZRotation(float angle);
};

class ShearMat : public Matrix {
    public:
    ShearMat(float xy, float xz, float yx, float yz, float zx, float zy);
};

float det3D(float* elems);
void getSubMat4D(const float* inputElems, float* outElems, int excludeRow, int excludeCol);

#endif