#include <iostream>
#include "PngWriter.hpp"

// to build:
//
// g++ main.cpp -lpng 

int main(int argc, char *argv[]) {
    PngWriter png(800, 600);

    // set some pixels....
//    for (int i = 0; i < 800; ++i)
//        for (int j = 0; j < 600; ++j)
//            png.set(i, j, 1, 1, 1); // set function assumes (0,0) is bottom left

    // then write...
    png.write("out/sample.png");
}

