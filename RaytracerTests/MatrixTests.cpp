#include "pch.h"

#include "../RayTracer/Matrix.h"

TEST(MatrixTests, Matrix4ConstructionTest) {
	Matrix<double, 4> m { 1.0, 2.0, 3.0, 4.0,
						5.5, 6.5, 7.5, 8.5,
						9.0, 10.0, 11.0, 12.0,
						13.5, 14.5, 15.5, 16.5 };

	ASSERT_EQ(m.data[0], 1);
	ASSERT_EQ(m.data[3], 4);
	ASSERT_EQ(m.data[4], 5.5);
	ASSERT_EQ(m.data[6], 7.5);
	ASSERT_EQ(m.data[10], 11);
	ASSERT_EQ(m.data[12], 13.5);
	ASSERT_EQ(m.data[14], 15.5);
}

TEST(MatrixTests, Matrix3ConstructionTest) {
	Matrix<int, 3> m{ -3, 5, 0,
						1, -2, -7,
						0, 1, 1};

	ASSERT_EQ(m.data[0], -3);
	ASSERT_EQ(m.data[4], -2);
	ASSERT_EQ(m.data[8], 1);
}
TEST(MatrixTests, Matrix2ConstructionTest) {
	Matrix<int, 2> m{ -3, 5,
						1, -2 };

	ASSERT_EQ(m.data[0], -3);
	ASSERT_EQ(m.data[1], 5);
	ASSERT_EQ(m.data[2], 1);
	ASSERT_EQ(m.data[3], -2);
}

TEST(MatrixTests, MatrixEqualityTest) {
	Matrix<double, 4> m1{ 1.0, 2.0, 3.0, 4.0,
					5.5, 6.5, 7.5, 8.5,
					9.0, 10.0, 11.0, 12.0,
					13.5, 14.5, 15.5, 16.5 };

	Matrix<double, 4> m2{ 1.0, 2.0, 3.0, 4.0,
					5.5, 6.5, 7.5, 8.5,
					9.0, 10.0, 11.0, 12.0,
					13.5, 14.5, 15.5, 16.5 };

	ASSERT_EQ(m1, m2);
}


TEST(MatrixTests, MatrixInequalityTest) {
	Matrix<double, 4> m1{ 1.0, 2.0, 3.0, 4.0,
					5.5, 6.5, 7.5, 8.5,
					9.0, 10.0, 11.0, 12.0,
					13.5, 14.5, 15.5, 16.5 };

	Matrix<double, 4> m2{ 2.0, 2.0, 3.0, 4.0,
					5.5, 6.5, 7.5, 8.5,
					9.0, 2.0, 11.0, 12.0,
					13.5, 14.5, 15.5, 16.5 };

	ASSERT_NE(m1, m2);
}


TEST(MatrixTests, MatrixMultiplicationTest) {
	Matrix<int, 4> m1{ 1, 2, 3, 4,
					5, 6, 7, 8,
					9, 8, 7, 6,
					5, 4, 3, 2 };

	Matrix<int, 4> m2{ -2, 1, 2, 3,
					3, 2, 1, -1,
					4, 3, 6, 5,
					1, 2, 7, 8 };

	Matrix<int, 4> expected{ 20, 22, 50, 48,
		44, 54, 114, 108,
		40, 58, 110, 102,
		16, 26, 46, 42 };

	ASSERT_EQ(expected, m1 * m2);
}

TEST(MatrixTests, MatrixTupleMultiplicationTest) {
	Matrix<int, 4> m{ 1, 2, 3, 4,
					2, 4, 4, 2,
					8, 6, 4, 1,
					0, 0, 0, 1 };

	Tuple t{ 1, 2, 3, 1 };


	ASSERT_EQ(Tuple(18, 24, 33, 1), m * t);
}


TEST(MatrixTests, MatrixIdentityMultiplicationTest) {
	Matrix<double, 4> m{ 1.0, 2.0, 3.0, 4.0,
						5.5, 6.5, 7.5, 8.5,
						9.0, 10.0, 11.0, 12.0,
						13.5, 14.5, 15.5, 16.5 };


	ASSERT_EQ(m, m * I<double>);
}

TEST(MatrixTests, IdentityTupleMultiplicationTest) {
	Tuple t(1.0, 2.0, 3.0, 4.0);

	ASSERT_EQ(t, I<double> *t);
}


TEST(MatrixTests, MatrixTransposeTest) {

	Matrix<int, 4> m(0, 9, 3, 0,
						9, 8, 0, 8,
						1, 8, 5, 3,
						0, 0, 5, 8);

	Matrix<int, 4> expected(0, 9, 1, 0,
							9, 8, 8, 0,
							3, 0, 5, 5,
							0, 8, 3, 8);


	ASSERT_EQ(expected, m.Transposed());
}


TEST(MatrixTests, Matrix4InversionTest) {
	Matrix<double, 4> m(  8.0, -5.0,  9.0,  2.0,
					      7.0,  5.0,  6.0,  1.0,
					     -6.0,  0.0,  9.0,  6.0,
					     -3.0,  0.0, -9.0, -4.0);

	Matrix<double, 4> expected( -0.15385, -0.15385, -0.28205, -0.53846,
								-0.07692, 0.12308, 0.02564, 0.03077,
								 0.35897, 0.35897, 0.43590, 0.92308,
								-0.69231, -0.69231, -0.76923, -1.92308);

	ASSERT_EQ(expected, m.Inversed());
}


TEST(MatrixTests, Matrix4Inversion2Test) {
	Matrix<double, 4> m( 9.0,  3.0,  0.0,  9.0,
						-5.0, -2.0, -6.0, -3.0,
						-4.0,  9.0,  6.0,  4.0,
						-7.0,  6.0,  6.0,  2.0);
		
	Matrix<double, 4> expected(-0.04074, -0.07778,  0.14444, -0.22222,
							   -0.07778,  0.03333,  0.36667, -0.33333,
							   -0.02901, -0.14630, -0.10926,  0.12963,
								0.17778,  0.06667, -0.26667,  0.33333);

	ASSERT_EQ(expected, m.Inversed());
}

/* TODO: test
Scenario: Multiplying a product by its inverse
Given the following 4x4 matrix A:
| 3 | -9 | 7 | 3 |
| 3 | -8 | 2 | -9 |
| -4 | 4 | 4 | 1 |
| -6 | 5 | -1 | 1 |
And the following 4x4 matrix B:
| 8 | 2 | 2 | 2 |
| 3 | -1 | 7 | 0 |
| 7 | 0 | 5 | 4 |
| 6 | -2 | 0 | 5 |
And C ? A * B
Then C * inverse(B) = A*/




TEST(MatrixTests, MatrixTranslationTest) {
	auto transform = I<double>.Translated(5.0, -3.0, 2.0);
	Point<int> p{ -3, 4, 5 };

	ASSERT_EQ(Point<int>(2, 1, 7), transform * p );
}
TEST(MatrixTests, MatrixTranslation2Test) {
	auto Itransform = I<double>.Translated(5.0, -3.0, 2.0).Inversed();
	Point<int> p{ -3, 4, 5 };

	ASSERT_EQ(Point<int>(-8, 7, 3), Itransform * p );
}
TEST(MatrixTests, MatrixTranslation3Test) {
	auto transform = I<double>.Translated(5.0, -3.0, 2.0);
	Vector<int> v{ -3, 4, 5 };

	ASSERT_EQ(v, transform * v );
	ASSERT_EQ(v, transform.Inversed() * v );
}



TEST(MatrixTests, MatrixScaleTest) {
	auto transform = I<double>.Scaled(2.0, 3.0, 4.0);
	Point<int> p{ -4, 6, 8 };

	ASSERT_EQ(Point<int>(-8, 18, 32), transform * p );
}

TEST(MatrixTests, MatrixScale2Test) {
	auto transform = I<double>.Scaled(2.0, 3.0, 4.0);
	Vector<int> v{ -4, 6, 8 };

	ASSERT_EQ(Vector<int>(-8, 18, 32), transform * v );
}

TEST(MatrixTests, MatrixScale3Test) {
	auto Itransform = I<double>.Scaled(2.0, 3.0, 4.0).Inversed();
	Vector<int> v{ -4, 6, 8 };

	ASSERT_EQ(Vector<int>(-2, 2, 2), Itransform * v );
}

#include <numbers>
TEST(MatrixTests, MatrixRotationTest) {
	using namespace std::numbers;
	auto half_quarter = I<double>.RotatedX(pi/4.0);
	auto full_quarter = I<double>.RotatedX(pi/2.0);
	Point<double> p{ 0.0, 1.0, 0.0 };

	ASSERT_EQ(Point<double>(0.0, sqrt2/2.0, sqrt2 / 2.0), half_quarter * p );
	ASSERT_EQ(Point<double>(0.0, 0.0, 1.0), full_quarter * p );
}