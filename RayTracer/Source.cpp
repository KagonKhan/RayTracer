#include "Vector.h"
#include "Canvas.hpp"
#include <chrono>
template<typename Canvas>
constexpr void render(Canvas& c) {
    for (int row = 0; row < Canvas::height; row++) {
        for (int col = 0; col < Canvas::width; col++) {
            c.canvas[row][col] = Color<double>(row, col, row+col).clamped();
        }
    }
}
using namespace std::literals::chrono_literals;

int main() {
    Canvas<7680, 4320, double> c;
    
    auto t1 = std::chrono::high_resolution_clock::now();
    render(c);
    auto t2 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    c.toPPM();
    auto t4 = std::chrono::high_resolution_clock::now();



    std::cout << std::chrono::duration_cast<std::chrono::seconds>(t4 - t3) << std::endl;
}
