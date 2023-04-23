#pragma once
#include "World.h"


struct Size {
    int width{ 1920 }, height{ 1080 };
} defaultSize;

template <typename T, Size = defaultSize>
class Camera {
private:
    Size size;
    T halfWidth;
    T halfHeight;
    T fieldOfView;
    T pxsize;

    Ray<T> r;
    int row = 0;
    int col = 0;

     
    constexpr void AimRayAt(Ray r, int row, int col) const noexcept {
        double xoffset = (col + 0.5) * pxsize;
        double yoffset = (row + 0.5) * pxsize;

        double world_x = halfWidth - xoffset;
        double world_y = halfHeight - yoffset;


        Point pixel = camInverse * new Point(world_x, world_y, -1);

        r.origin = camInverse * new Point(0, 0, 0);
        r.direction = (pixel - r.origin).Normalized();
    }

public:
    Matrix<T, 4> camInverse = new (Matrix<T, 4>::I);
    Matrix<T, 4> transform = new (Matrix<T, 4>::I);


    constexpr Camera(Size s, double fov) noexcept
        : size(s), fieldOfView(fov) {

        double half_view = Math.Tan(fov / 2);
        double aspect = (width / height);

        if (aspect >= 1) {
            halfWidth = half_view;
            halfHeight = half_view / aspect;
        }
        else {
            halfWidth = half_view * aspect;
            halfHeight = half_view;
        }

        pxsize = 2 * halfWidth / width;
    }


    constexpr Color<T> RenderRealTime(World w) const noexcept {

        AimRayAt(r, row, col);

        col++;
        if (col >= width) {
            col = 0;
            row++;
        }

        return w.Coloring(r);
    }

    constexpr Color<T> RenderRealTime(int y, int x, World w) const noexcept {
        AimRayAt(r, y, x);
        return w.Coloring(r);
    }

    Canvas RenderToCanvas(World w)
    {
        Canvas retVal(height, width);

        Color c;

        for (int row = 0; row < height; row++)
            for (int col = 0; col < width; col++)
            {
                AimRayAt(ref r, row, col);
                c = w.Coloring(r);

                retVal.WritePixel(row, col, c);

                // Progress report
                if ((row * width + col) % 10000 == 0)
                    Console.WriteLine($"{((row * width + col)/1000)} out of {height * width / 1000}");

            }

        return retVal;
    }

};