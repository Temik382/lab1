#include "pch.h"
#include <math.h>
#include <iostream>
#include <string>
#include <tuple>
#include <stdexcept>


/**
 * @brief ��������� ����� ���� ����������� �����.
 *
 * @param num1 ����� ����� (0�99).
 * @return ����� ���� �����; ���� ����� ������ 99, ������������ std::numeric_limits<int>::max().
 */
int sum_of_digits(int num1) {
	int n1, n2;
	if (num1 > 99) {
		return std::numeric_limits<int>::max();
	}
	else {
		n1 = num1 / 10;
		n2 = num1 % 10;
		return n1 + n2;

	}
}



/**
 * @brief ��������� ��������� ����� ����������� ����� � ������.
 *
 * ��������, 123 ������������ � 312.
 *
 * @param num1 ���������� ����� ����� (100�999).
 * @return ����� � �������������� ��������� ������.
 * @throw std::invalid_argument ���� ����� �� �������� ����������.
 */
int digit_perm(int num1) {
	if (num1 > 999) {
		return std::numeric_limits<int>::max();
	}
	else {
		int n1 = num1 % 10;
		int ost = num1 / 10;
		int res = n1 * 100 + ost;
		return res;
	}
}

/**
 * @brief ����������, ������� ��������� �� �������� c ���������� � ������������� a � b.
 *
 * @param a ������� �������������� (> 0).
 * @param b ������� �������������� (> 0).
 * @param c ������� �������� (> 0).
 * @return std::tuple<int, int> � ���������� ���������� ��������� � ���������� �������.
 * @throw std::invalid_argument ���� ����� �� �������� ���������������.
 */
std::tuple<int, int> squares_in_rect(int a, int b, int c) {
	if (a <= 0 || b <= 0 || c <= 0) {
		throw std::invalid_argument("All values must be positive");
	}
	int rect_area = a * b;
	int square_area = pow(c, 2);
	int count = rect_area / square_area;
	int rest_area = rect_area - (count * square_area);

	return std::make_tuple(count, rest_area);
}

// ---------- sum_of_digits ----------

/**
 * @brief Проверяет сумму цифр числа 45.
 */
TEST(sum_of_digits, sum45) {
	int num = 45;
	int a = sum_of_digits(num);
	int result_etalon = 9;
	EXPECT_EQ(a, result_etalon);
}

/**
 * @brief Проверяет возврат предельного значения для числа 178.
 */
TEST(sum_of_digits, sum_178) {
	int num = sum_of_digits(178);
	ASSERT_EQ(num, std::numeric_limits<int>::max());
}

/**
 * @brief Проверяет сумму цифр числа 99.
 */
TEST(sum_of_digits, sum99) {
	int num = 99;
	int a = sum_of_digits(num);
	int result_etalon = 18;
	EXPECT_EQ(a, result_etalon);
}

// ---------- digit_perm ----------

/**
 * @brief Проверяет перестановку последней цифры числа 123.
 */
TEST(digit_perm, perm123) {
	int num = 123;
	int a = digit_perm(num);
	int result_etalon = 312;
	EXPECT_EQ(a, result_etalon);
}

/**
 * @brief Проверяет возврат предельного значения для числа 1789.
 */
TEST(digit_perm, sum_1789) {
	int num = digit_perm(1789);
	ASSERT_EQ(num, std::numeric_limits<int>::max());
}

/**
 * @brief Проверяет перестановку цифр числа 907.
 */
TEST(digit_perm, perm907) {
	int num = 907;
	int a = digit_perm(num);
	int result_etalon = 790;
	EXPECT_EQ(a, result_etalon);
}

// ---------- squares_in_rect ----------

/**
 * @brief Проверяет количество квадратов и остаток при делении площадей 50 и 9.
 */
TEST(squares_in_rect, rect10x5sq3) {
	int a = 10, b = 5, c = 3;
	auto [count, rest] = squares_in_rect(a, b, c);
	int count_etalon = 5;
	int rest_etalon = 5;
	EXPECT_EQ(count, count_etalon);
	EXPECT_EQ(rest, rest_etalon);
}

/**
 * @brief Проверяет отсутствие остатка при делении площадей 36 и 9.
 */
TEST(squares_in_rect, rect6x6sq3) {
	int a = 6, b = 6, c = 3;
	auto [count, rest] = squares_in_rect(a, b, c);
	int count_etalon = 4;
	int rest_etalon = 0;
	EXPECT_EQ(count, count_etalon);
	EXPECT_EQ(rest, rest_etalon);
}

/**
 * @brief Проверяет исключение при нулевой стороне квадрата.
 */
TEST(squares_in_rect, zeroSquareSide) {
	int a = 10, b = 5, c = 0;
	EXPECT_THROW(squares_in_rect(a, b, c), std::invalid_argument);
}

/**
 * @brief Проверяет исключение при отрицательной стороне прямоугольника.
 */
TEST(squares_in_rect, negativeRectSide) {
	int a = -10, b = 5, c = 3;
	EXPECT_THROW(squares_in_rect(a, b, c), std::invalid_argument);
}