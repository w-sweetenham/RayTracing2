#include "Canvas.h"

Canvas::Canvas(int numRows, int numCols): numRows(numRows), numCols(numCols) {
    pixels = new float[numRows*numCols*3]; 
}

Canvas::Canvas(int numRows, int numCols, const Colour& initPixVal): numRows(numRows), numCols(numCols) {
    pixels = new float[numRows*numCols*3];
    float red = initPixVal.getRed();
    float green = initPixVal.getGreen();
    float blue = initPixVal.getBlue();
    for(int row=0; row<numRows; row++) {
        for(int col=0; col<numCols; col++) {
            pixels[(row*numCols*3) + (col*3)] = red;
            pixels[(row*numCols*3) + (col*3) + 1] = green;
            pixels[(row*numCols*3) + (col*3) + 2] = blue;
        }
    }
}

Canvas::~Canvas() {
    delete [] pixels;
}

void Canvas::setPixel(int row, int col, const Colour& colour) {
    pixels[(row*numCols*3) + (col*3)] = colour.getRed();
    pixels[(row*numCols*3) + (col*3) + 1] = colour.getGreen();
    pixels[(row*numCols*3) + (col*3) + 2] = colour.getBlue();
}

Colour Canvas::getPixel(int row, int col) const {
    return Colour(pixels[(row*numCols*3) + (col*3)], pixels[(row*numCols*3) + (col*3) + 1], pixels[(row*numCols*3) + (col*3) + 2]);
}

void Canvas::saveImage(std::string path) const {
    std::ofstream outFile;
    outFile.open(path);
    if(outFile.is_open()) {
        outFile << "P3" << '\n' << std::flush;
        outFile << numCols << ' ' << numRows << '\n' << std::flush;
        outFile << 255 << '\n' << std::flush;
        for(int row=0; row<numRows; row++) {
            for(int col=0; col<numCols; col++) {
                outFile << int(255.0*pixels[(row*numCols*3) + (col*3)]) << ' ' << std::flush;
                outFile << int(255.0*pixels[(row*numCols*3) + (col*3) + 1]) << ' ' << std::flush;
                outFile << int(255.0*pixels[(row*numCols*3) + (col*3) + 2]) << ' ' << std::flush;
                outFile << '\n' << std::flush;
            }
        }
        outFile.close();
        std::cout << "Image saved: " << std::endl;
    } else {
        std::cout << "Couldn't open: " << path << std::endl;
    }
}