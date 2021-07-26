#ifndef CANVAS_H_
#define CANVAS_H_

#include <iostream>
#include <fstream>

#include "src/basicConstructs/Colour.h"

class Canvas {
    private:
    float* pixels;
    int numRows;
    int numCols;

    public:
    Canvas(int numRows, int numCols);
    Canvas(int numRows, int numCols, const Colour& initPixVal);
    ~Canvas();
    void setPixel(int row, int col, const Colour& colour);
    Colour getPixel(int row, int col) const;
    void saveImage(std::string path) const;
};

#endif