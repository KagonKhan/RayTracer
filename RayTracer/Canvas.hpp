#pragma once
#pragma once 
#include <cstdlib>
#include <array>
#include <sstream>

#include "Vector.h"

template <std::size_t width, std::size_t height, typename T>
class Canvas
{
public:
    std::array<std::array< Color<T>, width>, height> canvas;

    void Flush(const Color<T>& color) {
        for (int row = 0; row < height; row++)
            for (int col = 0; col < width; col++)
                canvas[row, col] = color;
    }

    void WritePixel(int row, int col, const Color<T>& c) {
        if (col >= width || col < 0 || row >= height || row < 0)
            return;


        canvas[row][col] = ClampR(c);
    }

    // Artifacts: no space after color values in file

    void ToPPM() {
        std::ostringstream ss;

        ss << "P3\n{width} {height}\n255\n";

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                ss << canvas[row][col] << " ";
            }
            ss << '\n';
        }
        std::ofstream outFile("canvas.ppm");

        outFile << ss.rdbuf();
    }
};
