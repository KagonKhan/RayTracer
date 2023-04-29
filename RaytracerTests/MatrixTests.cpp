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

