#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <vector>
#include <algorithm>

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
    Object* objPtr;
    public:
    Intersection(float t, Object* objPtr);
    Intersection(const Intersection& other);
    float getT() const;
    Object* getObj() const;
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
    bool getHit(Intersection& intersection, Object*& prevObj, Object*& nextObj, Object* const defaultObj);
};

#endif