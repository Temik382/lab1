#include "pch.h"
#include <math.h>
#include <iostream>
#include <string>
#include <tuple>


int ex_7(int num1) {
	int n1, n2;
	n1 = num1 / 10;
	n2 = num1 % 10;
	return n1 + n2;
}

int ex_14(int num1) {
	int n1 = num1 % 10;
	int ost = num1 / 10;
	int res = n1 * 100 + ost;
	return res;
}

std::tuple<int, int> ex_29(int a, int b, int c) {
	int s_pryamoug = a * b;
	int s_kvadr = pow(c, 2);
	int count = s_pryamoug / s_kvadr;
	int ost_s = s_pryamoug - (count * s_kvadr);

	return std::make_tuple(count, ost_s);
}


TEST(Ex7, summa45) {
	EXPECT_EQ(ex_7(45), 9);
}

TEST(Ex7, summa99) {
	EXPECT_EQ(ex_7(99), 18);
}

TEST(Ex7, FAILING_summa23) {
	EXPECT_EQ(ex_7(23), 6);
}


TEST(Ex14, perestanovka123) {
	EXPECT_EQ(ex_14(123), 312);
}

TEST(Ex14, perestanovka907) {
	EXPECT_EQ(ex_14(907), 790);
}

TEST(Ex14, FAILING_perestanovka456) { 
	EXPECT_EQ(ex_14(456), 654);
}


TEST(Ex29, kvadraty10x5c3) {
	auto [count, ost] = ex_29(10, 5, 3);
	EXPECT_EQ(count, 5);
	EXPECT_EQ(ost, 5);
}

TEST(Ex29, kvadratyVlazitRyadno) {
	auto [count, ost] = ex_29(6, 6, 3);
	EXPECT_EQ(count, 4);
	EXPECT_EQ(ost, 0);
}

TEST(Ex29, FAILING_kvadraty10x5c3) { 
	auto [count, ost] = ex_29(10, 5, 3);
	EXPECT_EQ(count, 6);
	EXPECT_EQ(ost, 5);
}