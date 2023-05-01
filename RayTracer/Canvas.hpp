#pragma once
#pragma once 
#include <cstdlib>
#include <array>
#include <sstream>

#include "Vector.h"
#include <fstream>
#include <iostream>

#include "fast_io/include/fast_io.h"
#include "fast_io_device.h"


template <std::size_t Width, std::size_t Height, typename T>
class Canvas
{
public:
    static constexpr std::size_t width = Width;
    static constexpr std::size_t height = Height;
    using type = T;


    std::array<std::array< Color<T>, Width>, Height> canvas;

    constexpr void print() const noexcept {
        for (auto row : canvas) {
            for (auto value : row) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }

    constexpr void flush(Color<T> const& color) noexcept {
        for (int row = 0; row < Height; row++)
            for (int col = 0; col < Width; col++)
                canvas[row, col] = color;
    }

    constexpr void writePixel(int row, int col, const Color<T>& c) noexcept{
        if (col >= Width || col < 0 || row >= Height || row < 0)
            return;

        canvas[row][col] = ClampR(c);
    }

    // Artifacts: no space after color values in file

    constexpr void toPPM() const  {
        std::ostringstream ss;

        ss <<
            "P3\n" <<
            Width << " " << Height << "\n" <<
            "255\n";

        for (int row = 0; row < Height; row++) {
            for (int col = 0; col < Width; col++) {
                ss << canvas[row][col] << " ";
            }
            ss << '\n';
        }

        std::ofstream outFile("canvas3.ppm");
        outFile << ss.str();
        outFile.close();
    }

    constexpr void toPPMFast() const  {
        fast_io::obuf_file outFile("canvas.ppm");
        fast_io::io::println(outFile, "P3");
        fast_io::io::println(outFile, Width, " ", Height);
        fast_io::io::println(outFile, 255);

        for (int row = 0; row < Height; row++) {
            for (int col = 0; col < Width; col++) {
                fast_io::io::print(outFile,
                    canvas[row][col].red(), " ",
                    canvas[row][col].green(), " ",
                    canvas[row][col].blue(), " ");
            }
            fast_io::io::println (outFile);
        }
    }
};
