#ifndef INTERSECTION_H_
#define INTERSECTION_H_

class Object;

class Intersection {
    private:
    float t;
    Object* objPtr;
    public:
    Intersection(float t, Object* objPtr);
    float getT() const;
    Object* getObj() const;
};

#endif