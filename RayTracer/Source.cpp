#include "Vector.h"
#include "Canvas.hpp"
#include <chrono>
#include <algorithm>



template<typename Canvas>
constexpr void render(Canvas& c) {
    for (int row = 0; row < Canvas::height; row++) {
        for (int col = 0; col < Canvas::width; col++) {
            auto color{ Color<typename Canvas::type>(row % 256, col % 256, (row * col) % 256).clamped() };
            auto test = c.canvas[row][col];
            std::swap(color, test);
        }
    }
}
using namespace std::literals::chrono_literals;

auto process() {
    //Canvas<7680, 4320, std::uint8_t> c;
    //Canvas<1920, 1080, double> c;
    //Canvas<250, 250, double> c;
    Canvas<100, 100, double> c;
    render(c);
    return c;
}

void timer(auto function) {
    auto t3 = std::chrono::high_resolution_clock::now();
    std::invoke(function);
    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3) << std::endl;
}

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto x = process();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) << std::endl;


    //timer([&] {x.toPPMFast(); });
}
