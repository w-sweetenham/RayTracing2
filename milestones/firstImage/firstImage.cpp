#include <filesystem>
#include <iostream>

#include "src/camera/Canvas.h"
#include "src/basicConstructs/Colour.h"

int main() {
    Canvas c(400, 600);
    for(int row=0; row<400; row++) {
        for(int col=0; col<600; col++) {
            c.setPixel(row, col, Colour(0, 1, 0));
        }
    }
    std::filesystem::path save_path = std::filesystem::current_path() / "firstImage.ppm";
    c.saveImage(save_path);
}