#include "Vector.h"
#include "Canvas.hpp"
#include <chrono>
#include <algorithm>
#include "Auxiliary.h"
#include "Objects.h"

#include <iostream>
constexpr void AimRayAt(Ray<double>& r, int row, int col) noexcept {



}

template<typename Canvas>
constexpr void render(Canvas& c) {
    HitObject<double, Sphere<double>> sphere{ Sphere<double>{} };

    double wall_z = 10.0;
    double wall_size = 7.0;
    double pixel_size = wall_size / 250.0;
    double half = wall_size / 2.0;



    for (int row = 0; row < Canvas::height; row++) {
        double world_y = half - pixel_size * row;

        for (int col = 0; col < Canvas::width; col++) {
            
            double world_x = -half + pixel_size * col;
            Point<double> pixel{ world_x, world_y, (double)wall_z };
            

            auto origin = Point<double>(0, 0, -5);
            Ray<double> r{ .origin = origin, .direction = (pixel - origin).normalized() };


            auto idx = row * Canvas::width + col;

            c.canvas[row][col] = (sphere.IntersectionsWith(r).has_value()) ? Constants::Red<std::uint8_t> : Constants::Black<std::uint8_t>;


        }
    }
}

using namespace std::literals::chrono_literals;

constexpr auto process() {
    //Canvas<7680, 4320, std::uint8_t> c;
    //Canvas<1920, 1080, double> c;
    //Canvas<250, 250, std::uint8_t> c;
    Canvas<250, 250, std::uint8_t> c;
    render(c);
    return c;
}

constexpr void timer(auto const& function) {
    auto t3 = std::chrono::high_resolution_clock::now();
    std::invoke(function);
    auto t4 = std::chrono::high_resolution_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t4 - t3) << std::endl;
}

int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    constexpr auto x = process();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) << std::endl;

    //x.toPPMFast();
    timer([&] {x.toPPMFast(); });
}
