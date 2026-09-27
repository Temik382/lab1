#include "pch.h"
#include <iostream>
#include <tuple>
#include <cmath>

using namespace std;

double discr(double a, double b, double c) {
	return pow(b, 2) - 4 * a * c;
}

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




TEST(QuadEquation, NoRoots) {
	double a = 13;
	double b = 2;
	double c = 40;


	double x1, x2;
	tie(x1, x2) = corni(a, b, c);

	ASSERT_TRUE(isnan(x1));
	ASSERT_TRUE(isnan(x2));

}

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