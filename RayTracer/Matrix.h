#pragma once
#include <array>
#include <iostream>


template <typename T, std::size_t Dimension>
class Matrix {
private:
	inline static constexpr std::size_t dim{ Dimension * Dimension };
	std::array<T, dim> data;

	inline static constexpr std::size_t mapIndex(const std::size_t col, const std::size_t row) {
		return Dimension * row + col;
	}
public:
	constexpr Matrix() noexcept : data{ } { }
    template <typename... Ts> constexpr Matrix(Ts&&... ts) noexcept : data{ std::forward<Ts>(ts)... } {}
	
	constexpr friend std::ostream& operator<<(std::ostream& os, const Matrix& m) noexcept {
		for (std::size_t row = 0; row < Dimension; ++row) {
			for (std::size_t col = 0; col < Dimension; ++col) {
				os << m.data[mapIndex(col, row)] << (((col + 1) != Dimension) ? ", " : "\n");
			}
		}
		return os;
	}





    /*

    public readonly static Mat4 I = new Mat4(1.0d, 0.0d, 0.0d, 0.0d,
        0.0d, 1.0d, 0.0d, 0.0d,
        0.0d, 0.0d, 1.0d, 0.0d,
        0.0d, 0.0d, 0.0d, 1.0d);

    public Mat4(double a, double b, double c, double d,
        double e, double f, double g, double h,
        double i, double j, double k, double l,
        double m, double n, double o, double p) : base(4)
    {
        mat[0] = a;  mat[1] = b;  mat[2] = c;  mat[3] = d;
        mat[4] = e;  mat[5] = f;  mat[6] = g;  mat[7] = h;
        mat[8] = i;  mat[9] = j;  mat[10] = k;  mat[11] = l;
        mat[12] = m;  mat[13] = n;  mat[14] = o;  mat[15] = p;
    }
    public Mat4(int zero) : base(4) {}
    public Mat4(in Mat4 copy) : base(4)
    {
        for (int row = 0; row < 4; row++)
            for (int col = 0; col < 4; col++)
                this[row, col] = copy[row, col];
    }

    public Mat4(in Vector r1, in Vector r2, in Vector r3, in Vector r4) : base(4)
    {
        for (int col = 0; col < 4; col++)
        {
            this[0, col] = r1[col];
            this[1, col] = r2[col];
            this[2, col] = r3[col];
            this[3, col] = r4[col];
        }
    }

    public static Mat4 operator *(in Mat4 a, in Mat4 b)
    {
        double v1 = a[0, 0] * b[0, 0] + a[0, 1] * b[1, 0] + a[0, 2] * b[2, 0] + a[0, 3] * b[3, 0];
        double v2 = a[0, 0] * b[0, 1] + a[0, 1] * b[1, 1] + a[0, 2] * b[2, 1] + a[0, 3] * b[3, 1];
        double v3 = a[0, 0] * b[0, 2] + a[0, 1] * b[1, 2] + a[0, 2] * b[2, 2] + a[0, 3] * b[3, 2];
        double v4 = a[0, 0] * b[0, 3] + a[0, 1] * b[1, 3] + a[0, 2] * b[2, 3] + a[0, 3] * b[3, 3];

        double v5 = a[1, 0] * b[0, 0] + a[1, 1] * b[1, 0] + a[1, 2] * b[2, 0] + a[1, 3] * b[3, 0];
        double v6 = a[1, 0] * b[0, 1] + a[1, 1] * b[1, 1] + a[1, 2] * b[2, 1] + a[1, 3] * b[3, 1];
        double v7 = a[1, 0] * b[0, 2] + a[1, 1] * b[1, 2] + a[1, 2] * b[2, 2] + a[1, 3] * b[3, 2];
        double v8 = a[1, 0] * b[0, 3] + a[1, 1] * b[1, 3] + a[1, 2] * b[2, 3] + a[1, 3] * b[3, 3];

        double v9 = a[2, 0] * b[0, 0] + a[2, 1] * b[1, 0] + a[2, 2] * b[2, 0] + a[2, 3] * b[3, 0];
        double v10 = a[2, 0] * b[0, 1] + a[2, 1] * b[1, 1] + a[2, 2] * b[2, 1] + a[2, 3] * b[3, 1];
        double v11 = a[2, 0] * b[0, 2] + a[2, 1] * b[1, 2] + a[2, 2] * b[2, 2] + a[2, 3] * b[3, 2];
        double v12 = a[2, 0] * b[0, 3] + a[2, 1] * b[1, 3] + a[2, 2] * b[2, 3] + a[2, 3] * b[3, 3];

        double v13 = a[3, 0] * b[0, 0] + a[3, 1] * b[1, 0] + a[3, 2] * b[2, 0] + a[3, 3] * b[3, 0];
        double v14 = a[3, 0] * b[0, 1] + a[3, 1] * b[1, 1] + a[3, 2] * b[2, 1] + a[3, 3] * b[3, 1];
        double v15 = a[3, 0] * b[0, 2] + a[3, 1] * b[1, 2] + a[3, 2] * b[2, 2] + a[3, 3] * b[3, 2];
        double v16 = a[3, 0] * b[0, 3] + a[3, 1] * b[1, 3] + a[3, 2] * b[2, 3] + a[3, 3] * b[3, 3];


        return new Mat4(v1, v2, v3, v4,
            v5, v6, v7, v8,
            v9, v10, v11, v12,
            v13, v14, v15, v16);
    }

    public static Vector operator *(in Mat4 a, in Vector b)
    {
        double v1 = a[0, 0] * b[0] + a[0, 1] * b[1] + a[0, 2] * b[2] + a[0, 3] * b[3];
        double v2 = a[1, 0] * b[0] + a[1, 1] * b[1] + a[1, 2] * b[2] + a[1, 3] * b[3];
        double v3 = a[2, 0] * b[0] + a[2, 1] * b[1] + a[2, 2] * b[2] + a[2, 3] * b[3];
        double v4 = a[3, 0] * b[0] + a[3, 1] * b[1] + a[3, 2] * b[2] + a[3, 3] * b[3];

        return new Vector(v1, v2, v3, v4);
    }

    public static Point operator *(in Mat4 a, in Point b)
    {
        double v1 = a[0, 0] * b[0] + a[0, 1] * b[1] + a[0, 2] * b[2] + a[0, 3] * b[3];
        double v2 = a[1, 0] * b[0] + a[1, 1] * b[1] + a[1, 2] * b[2] + a[1, 3] * b[3];
        double v3 = a[2, 0] * b[0] + a[2, 1] * b[1] + a[2, 2] * b[2] + a[2, 3] * b[3];
        double v4 = a[3, 0] * b[0] + a[3, 1] * b[1] + a[3, 2] * b[2] + a[3, 3] * b[3];

        return new Point(v1, v2, v3, v4);
    }
    // unoptimized
    public Mat4 Transposed()
    {
        Mat4 retVal = new Mat4(0);
        for (int row = 0; row < 4; row++)
            for (int col = 0; col < 4; col++)
                retVal[col, row] = this[row, col];

        return retVal;
    }
    public Mat3 Sub(int r, int c)
    {
        Mat3 retVal = new Mat3();

        for (int row = 0, rIndex = 0; row < 4; row++)
        {
            if (row == r)
                continue;

            for (int col = 0, cIndex = 0; col < 4; col++)
            {
                if (col == c)
                    continue;

                retVal[rIndex, cIndex] = this[row, col];

                cIndex++;
            }
            rIndex++;
        }

        return retVal;
    }
    public double Minor(int r, int c)
    {
        return Sub(r, c).Determinant();
    }
    public double Cofactor(int r, int c)
    {
        return (r + c) % 2 == 0 ? Minor(r, c) : -Minor(r, c);
    }
    public double Determinant()
    {
        return mat[0] * Cofactor(0, 0) + mat[1] * Cofactor(0, 1) + mat[2] * Cofactor(0, 2) + mat[3] * Cofactor(0, 3);
    }
    public bool Inversible()
    {
        return Determinant() != 0;
    }

    // Copies original matrix
    public Mat4 Inversed()
    {

        Mat4 retVal = new Mat4(I);
        Mat4 a = new Mat4(this);

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (j != i)
                {
                    double ratio = a[j, i] / a[i, i];
                    a[j, 0] -= a[i, 0] * ratio;
                    a[j, 1] -= a[i, 1] * ratio;
                    a[j, 2] -= a[i, 2] * ratio;
                    a[j, 3] -= a[i, 3] * ratio;

                    retVal[j, 0] -= retVal[i, 0] * ratio;
                    retVal[j, 1] -= retVal[i, 1] * ratio;
                    retVal[j, 2] -= retVal[i, 2] * ratio;
                    retVal[j, 3] -= retVal[i, 3] * ratio;
                }

        for (int i = 0; i < 4; i++)
        {
            double temp = 1 / a[i, i];
            retVal[i, 0] = retVal[i, 0] * temp;
            retVal[i, 1] = retVal[i, 1] * temp;
            retVal[i, 2] = retVal[i, 2] * temp;
            retVal[i, 3] = retVal[i, 3] * temp;

        }

        return retVal;
    }
    public Mat4 InversedV2()
    {
        Matrix4x4 source = new Matrix4x4((float)mat[0], (float)mat[1], (float)mat[2], (float)mat[3],
            (float)mat[4], (float)mat[5], (float)mat[6], (float)mat[7],
            (float)mat[8], (float)mat[9], (float)mat[10], (float)mat[11],
            (float)mat[12], (float)mat[13], (float)mat[14], (float)mat[15]);

        Matrix4x4 ret = new();
        System.Numerics.Matrix4x4.Invert(source, out ret);

        return new Mat4(ret.M11, ret.M12, ret.M13, ret.M14,
            ret.M21, ret.M22, ret.M23, ret.M24,
            ret.M31, ret.M32, ret.M33, ret.M34,
            ret.M41, ret.M42, ret.M43, ret.M44);

    }

    // Destroys original matrix
    public Mat4 Inverse(bool checkIfProper = false)
    {
        if (checkIfProper && !Inversible())
            throw new ArithmeticException("Matrix not inversible");

        Mat4 retVal = new Mat4(I);

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (j != i)
                {
                    double ratio = this[j, i] / this[i, i];
                    this[j, 0] -= this[i, 0] * ratio;
                    this[j, 1] -= this[i, 1] * ratio;
                    this[j, 2] -= this[i, 2] * ratio;
                    this[j, 3] -= this[i, 3] * ratio;

                    retVal[j, 0] -= retVal[i, 0] * ratio;
                    retVal[j, 1] -= retVal[i, 1] * ratio;
                    retVal[j, 2] -= retVal[i, 2] * ratio;
                    retVal[j, 3] -= retVal[i, 3] * ratio;
                }

        for (int i = 0; i < 4; i++)
        {
            double temp = 1 / this[i, i];
            retVal[i, 0] = retVal[i, 0] * temp;
            retVal[i, 1] = retVal[i, 1] * temp;
            retVal[i, 2] = retVal[i, 2] * temp;
            retVal[i, 3] = retVal[i, 3] * temp;

        }

        return retVal;
    }


    public Mat4 Translated(double x, double y, double z)
    {
        return this * new Mat4(1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1);
    }
    public Mat4 Scaled(double x, double y, double z)
    {
        return this * new Mat4(x, 0, 0, 0,
            0, y, 0, 0,
            0, 0, z, 0,
            0, 0, 0, 1);
    }
    public Mat4 Sheared(double Xy = 0, double Xz = 0, double Yx = 0, double Yz = 0, double Zx = 0, double Zy = 0)
    {
        return this * new Mat4(1, Xy, Xz, 0,
            Yx, 1, Yz, 0,
            Zx, Zy, 1, 0,
            0, 0, 0, 1);
    }
    public Mat4 RotatedX(double r)
    {
        double c = Math.Cos(r), s = Math.Sin(r);

        return this * new Mat4(1, 0, 0, 0,
            0, c, -s, 0,
            0, s, c, 0,
            0, 0, 0, 1);
    }
    public Mat4 RotatedY(double r)
    {
        double c = Math.Cos(r), s = Math.Sin(r);

        return this * new Mat4(c, 0, s, 0,
            0, 1, 0, 0,
            -s, 0, c, 0,
            0, 0, 0, 1);
    }
    public Mat4 RotatedZ(double r)
    {
        double c = Math.Cos(r), s = Math.Sin(r);

        return this * new Mat4(c, -s, 0, 0,
            s, c, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    }


    */


};
