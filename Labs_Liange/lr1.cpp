#include "pch.h"
#include <iostream>
#include <tuple>
#include <cmath>

using namespace std;

/**
 * @brief Вычисляет дискриминант квадратного уравнения a*x*x + b*x + c = 0.
 * @param a Коэффициент при квадрате неизвестного.
 * @param b Коэффициент при неизвестном.
 * @param c Свободный член.
 * @return Значение b*b - 4*a*c.
 */
double discr(double a, double b, double c) {
	return pow(b, 2) - 4 * a * c;
}

/**
 * @brief Вычисляет действительные корни квадратного уравнения.
 * @param a Коэффициент при квадрате неизвестного; должен быть ненулевым.
 * @param b Коэффициент при неизвестном.
 * @param c Свободный член.
 * @return Кортеж двух корней при положительном дискриминанте; при нулевом — корень и 0; при отрицательном — два NaN.
 */
tuple<double, double> corni(double a, double b, double c) {

	double x1 = 0;
	double x2 = 0;

	double d = discr(a, b, c);

	if (d > 0) {
		x1 = (-b + sqrt(d)) / (2 * a);
		x2 = (-b - sqrt(d)) / (2 * a);
	}
	else if (d == 0) {
		x1 = -b / (2 * a);
	}
	else {
		x1 = std::numeric_limits<double>::quiet_NaN();
		x2 = std::numeric_limits<double>::quiet_NaN();
	}

	return make_tuple(x1, x2);
}



/**
 * @brief Проверяет соотношения Виета и различие действительных корней.
 */
TEST(QuadEquation, Vieta) {
	double a = 1;
	double b = 4;
	double c = 1;
		

	// double x1, x2;	
	// tie(x1, x2) = corni(a, b, c);

	auto [x1, x2] = corni(a, b, c);

	double e = abs(x1 - x2);
	bool are_different = e > std::numeric_limits<double>::epsilon();

	ASSERT_FALSE(isnan(x1));
	ASSERT_FALSE(isnan(x2));

	ASSERT_GT(e, numeric_limits<double>::epsilon());
	ASSERT_NEAR(x1 + x2, -(b / a), 1e-9); 
	ASSERT_NEAR(x1 * x2, c / a, 1e-9);

}




/**
 * @brief Проверяет получение двух NaN при отрицательном дискриминанте.
 */
TEST(QuadEquation, NoRoots) {
	double a = 13;
	double b = 2;
	double c = 40;


	double x1, x2;
	tie(x1, x2) = corni(a, b, c);

	ASSERT_TRUE(isnan(x1));
	ASSERT_TRUE(isnan(x2));

}

/**
 * @brief Проверяет наличие двух различных действительных корней.
 */
TEST(QuadEquation, Rootsfalse) {
	double a = 1;
	double b = 4;
	double c = 1;


	// double x1, x2;	
	// tie(x1, x2) = corni(a, b, c);

	auto [x1, x2] = corni(a, b, c);

	double e = abs(x1 - x2);
	bool are_different = e > std::numeric_limits<double>::epsilon();

	ASSERT_FALSE(isnan(x1));
	ASSERT_FALSE(isnan(x2));

	ASSERT_GT(e, numeric_limits<double>::epsilon());
	ASSERT_TRUE(are_different);

}