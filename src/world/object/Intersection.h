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
    bool hit;
    Vec norm;
    Point point;
    float ambient, diffuse, specular, shininess;
    float n1;
    float n2;
    float reflectivity;
    float transparency;
    Colour colour;
    Vec lightVec;
    Colour lightIntensity;
    bool isShadowed;
    IntersectionSpec(bool hit, 
                    const Vec& norm, 
                    const Point& point, 
                    float ambient, 
                    float diffuse, 
                    float specular, 
                    float shininess,
                    float n1,
                    float n2,
                    float reflectivity,
                    float transparency,
                    const Colour& colour, 
                    const Vec& lightVec, 
                    const Colour& intensity, 
                    bool isShadowed);
};

#endif