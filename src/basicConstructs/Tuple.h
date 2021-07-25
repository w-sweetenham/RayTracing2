#ifndef TUPLE_H_
#define TUPLE_H_

#include <iostream>
#include <math.h>

#include "src/utils/Utils.h"

class Point;
class Vec;
class Matrix;

class Tuple {
    friend class Vec;
    friend class Point;//Friend classes Vec and point so a point and vec can be created from a tuple with a copy constructor
    friend class Matrix;//This is so a matrix object can multiply a tuple

    protected:
    float elems[4];

    public:
    Tuple(float elem1, float elem2, float elem3);
    float getElem(int n) const;
    bool roughlyEqual(const Tuple& other) const;
    friend std::ostream& operator<< (std::ostream &out, const Tuple& tuple);
};

class Vec : public Tuple {
    friend class Point;
    friend class Matrix;

    public:
    Vec();
    Vec(float elem1, float elem2, float elem3);
    Vec(const Vec& other);
    const Vec& operator=(const Vec& other);
    Vec operator+(const Vec& other) const;
    Vec operator-(const Vec& other) const;
    Vec operator*(const float scalar) const;
    Vec operator/(const float scalar) const;
    Vec operator*(const Vec& other);
    void operator*=(float scalar);
    float mag() const;
    void normalize();
    float dot(const Vec& other) const;
};

class Point : public Tuple {
    friend class Vec;
    friend class Matrix;

    public:
    Point();
    Point(float elem1, float elem2, float elem3);
    Point(const Point& other);
    const Point& operator=(const Point& other);
    Point operator+(const Vec& vec) const;
    Point operator-(const Vec& vec) const;
    Vec operator-(const Point& other) const;
    void operator+=(const Vec& vec);
    void operator-=(const Vec& vec);
};

#endif