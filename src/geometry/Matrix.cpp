#include "Matrix.h"

Matrix::Matrix(float initVal) {
    for(int i=0; i<16; i++) {
        elems[i] = initVal;
    }
}

Matrix::Matrix(float* elems) {
    for(int i=0; i<16; i++) {
        this->elems[i] = elems[i];
    }
}
    
Matrix::Matrix(const Matrix& other) {
    for(int i=0; i<16; i++) {
        elems[i] = other.elems[i];
    }
}

const Matrix& Matrix::operator=(const Matrix& other) {
    for(int i=0; i<16; i++) {
        elems[i] = other.elems[i];
    }
    return *this;
}

float Matrix::getElem(int row, int col) const {
    return elems[(row*4) + col];
}

Vec Matrix::operator*(const Vec& vec) const {
    float newVec[3];
    for(int row=0; row < 3; row++) {
        newVec[row] = 0;
        for(int col=0; col<4; col++) {
            newVec[row] += elems[(4*row) + col] * vec.elems[col];
        }
    }
    return Vec(newVec[0], newVec[1], newVec[2]);
}

Point Matrix::operator*(const Point& point) const {
    float newPoint[3];
    for(int row=0; row < 3; row++) {
        newPoint[row] = 0;
        for(int col=0; col<4; col++) {
            newPoint[row] += elems[(4*row) + col] * point.elems[col];
        }
    }
    return Point(newPoint[0], newPoint[1], newPoint[2]);
}

IdentityMat::IdentityMat(): Matrix(0.0) {
    for(int i=0; i<16; i++) {
        if(i % 5 == 0) {
            elems[i] = 1.0;
        }
    }
}

Matrix Matrix::operator*(const Matrix& other) const {
    float newElems[16];
    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            float newElem = 0;
            for(int i=0; i<4; i++) {
                newElem += (elems[(row*4)+i] * other.elems[(i*4)+col]);
            }
            newElems[(row*4) + col] = newElem;
        }
    }
    return Matrix(newElems);
}

Matrix& Matrix::transpose() {
    float temp;
    for(int row=0; row<3; row++) {
        for(int col=row+1; col<4; col++) {
            temp = elems[(row*4) + col];
            elems[(row*4) + col] = elems[(col*4) + row];
            elems[(col*4) + row] = temp;
        }
    }
}

float det2D(float* elems) {
    return (elems[0]*elems[3] - elems[1]*elems[2]);
}

float det3D(float* elems) {
    float det;
    float submatrix[4];

    submatrix[0] = elems[(1*3) + 1];
    submatrix[1] = elems[(1*3) + 2];
    submatrix[2] = elems[(2*3) + 1];
    submatrix[3] = elems[(2*3) + 2];
    det += elems[0]*det2D(submatrix);

    submatrix[0] = elems[(1*3) + 0];
    submatrix[1] = elems[(1*3) + 2];
    submatrix[2] = elems[(2*3) + 0];
    submatrix[3] = elems[(2*3) + 2];
    det -= elems[1]*det2D(submatrix);

    submatrix[0] = elems[(1*3) + 0];
    submatrix[1] = elems[(1*3) + 1];
    submatrix[2] = elems[(2*3) + 0];
    submatrix[3] = elems[(2*3) + 1];
    det += elems[2]*det2D(submatrix);

    return det;
}

void getSubMat4D(const float* inputElems, float* outElems, int excludeRow, int excludeCol) {
    int currentIndex = 0;
    for(int row=0; row<4; row++) {
        for(int col=0; col<4; col++) {
            if(row != excludeRow && col != excludeCol) {
                outElems[currentIndex] = inputElems[(row*4) + col];
                currentIndex += 1;
            }
        }
    }
}

float det4D(const float* elems) {
    float det=0;
    float subDet;
    float subMat[9];
    for(int i=0; i<4; i++) {
        getSubMat4D(elems, subMat, 0, i);
        subDet = det3D(subMat);
        if(i % 2 == 0) {
            det += elems[i]*subDet;
        } else {
            det -= elems[i]*subDet;
        }
    }
    return det;
}

Matrix Matrix::getInverse() const {
    float det = det4D(elems);
    if(det > -0.00001 && det < 0.00001) {
        throw UnInvertible();
    } else {
        float cofactors[16];
        float subMat[9];
        float subDet;
        for(int row=0; row<4; row++) {
            for(int col=0; col<4; col++) {
                getSubMat4D(elems, subMat, row, col);
                subDet = det3D(subMat);
                if((row%2 != 0 && col%2 == 0) || (row%2 == 0 && col%2 != 0)) {
                    cofactors[(row*4) + col] = (-1.0*subDet)/det;
                } else {
                    cofactors[(row*4) + col] = subDet/det;
                }
            }
        }
        Matrix invMat(cofactors);
        invMat.transpose();
        return invMat;
    }
}

TranslationMat::TranslationMat(float x, float y, float z) : Matrix(0.0) {
    for(int i=0; i<4; i++) {
        elems[(i*4)+i] = 1.0;
    }
    elems[3] = x;
    elems[7] = y;
    elems[11] = z;
}

ScalingMat::ScalingMat(float x, float y, float z) : Matrix(0.0) {
    elems[0] = x;
    elems[5] = y;
    elems[10] = z;
    elems[15] = 1.0;
}

XRotation::XRotation(float angle): Matrix(0.0) {
    elems[0] = 1.0;
    elems[5] = cos(angle);
    elems[6] = -1.0*sin(angle);
    elems[9] = sin(angle);
    elems[10] = cos(angle);
    elems[15] = 1.0;
}

YRotation::YRotation(float angle): Matrix(0.0) {
    elems[0] = cos(angle);
    elems[2] = sin(angle);
    elems[5] = 1.0;
    elems[8] = -1.0*sin(angle);
    elems[10] = cos(angle);
    elems[15] = 1.0;
}

ZRotation::ZRotation(float angle): Matrix(0.0) {
    elems[0] = cos(angle);
    elems[1] = -1.0*sin(angle);
    elems[4] = sin(angle);
    elems[5] = cos(angle);
    elems[10] = 1.0;
    elems[15] = 1.0;
}

ShearMat::ShearMat(float xy, float xz, float yx, float yz, float zx, float zy): Matrix(0.0) {
    elems[0] = 1.0;
    elems[1] = xy;
    elems[2] = xz;
    elems[4] = yx;
    elems[5] = 1.0;
    elems[6] = yz;
    elems[8] = zx;
    elems[9] = zy;
    elems[10] = 1.0;
    elems[15] = 1.0;
}