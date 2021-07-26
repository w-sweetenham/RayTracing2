#include "Tuple.h"

Tuple::Tuple(float elem1, float elem2, float elem3) {
    elems[0] = elem1;
    elems[1] = elem2;
    elems[2] = elem3;
}

float Tuple::getElem(int n) const {
    return elems[n];
}

bool Tuple::roughlyEqual(const Tuple& other) const {
    if(::roughlyEqual(elems[0], other.elems[0]) && ::roughlyEqual(elems[1], other.elems[1]) && ::roughlyEqual(elems[2], other.elems[2]) && ::roughlyEqual(elems[3], other.elems[3])) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<< (std::ostream &out, const Tuple& tuple) {
    out << "Elem 0: " << tuple.elems[0] << "\nElem 1:" << tuple.elems[1] << "\nElem2: " << tuple.elems[2];

    return out;
}


Vec::Vec(): Tuple(0.0, 0.0, 0.0) {
    elems[3] = 0.0;
}

Vec::Vec(float elem1, float elem2, float elem3): Tuple(elem1, elem2, elem3) {
    elems[3] = 0.0;
}

Vec::Vec(const Vec& other): Tuple(other.elems[0], other.elems[1], other.elems[2]) {
    elems[3] = 0.0;
}

const Vec& Vec::operator=(const Vec& other) {
    elems[0] = other.elems[0];
    elems[1] = other.elems[1];
    elems[2] = other.elems[2];
}

Vec Vec::operator+(const Vec& other) const {
    return Vec(elems[0]+other.elems[0], elems[1]+other.elems[1], elems[2]+other.elems[2]);
}

Vec Vec::operator-(const Vec& other) const {
    return Vec(elems[0]-other.elems[0], elems[1]-other.elems[1], elems[2]-other.elems[2]);
}

Vec Vec::operator*(const float scalar) const {
    return Vec(elems[0]*scalar, elems[1]*scalar, elems[2]*scalar);
}

Vec Vec::operator/(const float scalar) const {
    return Vec(elems[0]/scalar, elems[1]/scalar, elems[2]/scalar);
}

Vec Vec::operator*(const Vec& other) const{
    return Vec(elems[1]*other.elems[2] - elems[2]*other.elems[1],
    elems[2]*other.elems[0] - elems[0]*other.elems[2],
    elems[0]*other.elems[1] - elems[1]*other.elems[0]);
}

void Vec::operator*=(float scalar) {
    elems[0] *= scalar;
    elems[1] *= scalar;
    elems[2] *= scalar;
}

float Vec::mag() const {
    return sqrt(elems[0]*elems[0] + elems[1]*elems[1] + elems[2]*elems[2]);
}

void Vec::normalize() {
    float mag = this->mag();
    elems[0] = elems[0]/mag;
    elems[1] = elems[1]/mag;
    elems[2] = elems[2]/mag;
}

float Vec::dot(const Vec& other) const {
    return elems[0]*other.elems[0] + elems[1]*other.elems[1] + elems[2]*other.elems[2];
}

Point::Point(): Tuple(0.0, 0.0, 0.0) {
    elems[3] = 1.0;
}

Point::Point(float elem1, float elem2, float elem3): Tuple(elem1, elem2, elem3) {
    elems[3] = 1.0;
}

Point::Point(const Point& other): Tuple(other.elems[0], other.elems[1], other.elems[2]) {
    elems[3] = 1.0;
}

const Point& Point::operator=(const Point& other) {
    elems[0] = other.elems[0];
    elems[1] = other.elems[1];
    elems[2] = other.elems[2];
}

Point Point::operator+(const Vec& vec) const {
    return Point(elems[0] + vec.elems[0], elems[1] + vec.elems[1], elems[2] + vec.elems[2]);
}

Vec Point::operator-(const Point& other) const {
    return Vec(elems[0] - other.elems[0], elems[1] - other.elems[1], elems[2] - other.elems[2]);
}

Point Point::operator-(const Vec& vec) const {
    return Point(elems[0] - vec.elems[0], elems[1] - vec.elems[1], elems[2] - vec.elems[2]);
}

void Point::operator+=(const Vec& vec) {
    elems[0] += vec.elems[0];
    elems[1] += vec.elems[1];
    elems[2] += vec.elems[2];
}
void Point::operator-=(const Vec& vec) {
    elems[0] -= vec.elems[0];
    elems[1] -= vec.elems[1];
    elems[2] -= vec.elems[2];
}

