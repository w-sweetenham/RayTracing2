#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <vector>
#include <algorithm>
#include "src/basicConstructs/Tuple.h"
#include "src/basicConstructs/Colour.h"

class Object;

class BadIndex: public std::exception {
    public:
    virtual const char* what() const throw() {
        return "Bad index used";
    }
};

class Intersection {
    private:
    float t;
    const Object* objPtr;
    public:
    Intersection(float t, const Object* objPtr);
    Intersection(const Intersection& other);
    float getT() const;
    const Object* getObj() const;
    bool operator<(const Intersection& other) const;
};

class IntersectionSet {
    private:
    std::vector<Intersection> posIntersections;
    std::vector<Intersection> negIntersections;
    public:
    void addIntersection(const Intersection& intersection);
    int getNumNegIntersections() const;
    int getNumPosIntersections() const;
    Intersection getPosIntersection(int index) const;
    Intersection getNegIntersection(int index) const;
    bool getHit(Intersection& intersection, const Object*& prevObj, const Object*& nextObj, const Object* const defaultObj);
};

struct IntersectionSpec {
    Vec norm;
    Point point;
    const Object* obj1;
    const Object* obj2;
    Vec lightVec;
    Colour lightIntensity;
    IntersectionSpec(const Vec& norm, const Point& point, const Object* obj1, const Object* obj2, const Vec& lightVec, const Colour& intensity);
};

#endif