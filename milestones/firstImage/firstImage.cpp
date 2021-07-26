#include "src/camera/Canvas.h"
#include "src/basicConstructs/Colour.h"

int main() {
    Canvas c(400, 600);
    for(int row=0; row<400; row++) {
        for(int col=0; col<600; col++) {
            c.setPixel(row, col, Colour(0, 1, 0));
        }
    }
    c.saveImage("/home/william/CPP/Projects/RayTracer2/milestones/firstImage/firstImage.ppm");
}