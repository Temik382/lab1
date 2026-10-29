#include "pch.h"
#include <iostream>
#include <tuple>
#include <cmath>
#include <string>


/**
 * @brief Проверяет, являются ли оба числа нечётными.
 *
 * @param num1 Первое целое число.
 * @param num2 Второе целое число.
 * @return true, если оба числа нечётные, иначе false.
 */
bool odd_nums(int num1, int num2) {
	if (num1 % 2 != 0 && num2 % 2 != 0)
		return true;
	else
		return false;
}

// ---------- odd_nums ----------

 
/**
 * @brief Проверяет два положительных нечётных числа.
 */
TEST(odd_nums, BothOdd) {
	// Arrange — подготовка данных
	int num1 = 3;
	int num2 = 7;

	// Act — вызов тестируемой функции
	bool result = odd_nums(num1, num2);

	// Assert — проверка результата
	EXPECT_TRUE(result);
}

/**
 * @brief Проверяет отказ при чётном первом числе.
 */
TEST(odd_nums, FirstEven) {
	// Arrange
	int num1 = 2;
	int num2 = 7;

	// Act
	bool result = odd_nums(num1, num2);

	// Assert
	EXPECT_FALSE(result);
}

/**
 * @brief Проверяет два отрицательных нечётных числа.
 */
TEST(odd_nums, BothNegativeOdd) {
	// Arrange
	int num1 = -3;
	int num2 = -5;

	// Act
	bool result = odd_nums(num1, num2);

	// Assert
	EXPECT_TRUE(result);
}

/**
 * @brief Определяет цвет клетки шахматной доски по координатам (0 - белая, 1 - чёрная).
 *
 * @param x Горизонтальная координата клетки (1–8).
 * @param y Вертикальная координата клетки (1–8).
 * @return true, если клетка чёрная (сумма координат чётная), иначе false.
 */
bool desk_of_chess(int x, int y) {
	return (x + y) % 2 == 0;
}

/**
 * @brief Проверяет чёрный цвет клетки A1.
 */
TEST(desk_of_chess, CornerA1IsBlack) {
	// Arrange — подготовка данных
	int x = 1;
	int y = 1;

	// Act — вызов тестируемой функции
	bool is_black = desk_of_chess(x, y);

	// Assert — проверка результата
	EXPECT_TRUE(is_black);
}

/**
 * @brief Проверяет чёрный цвет клетки H8.
 */
TEST(desk_of_chess, CornerH8IsBlack) {
	// Arrange
	int x = 8;
	int y = 8;

	// Act
	bool is_black = desk_of_chess(x, y);

	// Assert
	EXPECT_TRUE(is_black);
}

/**
 * @brief Проверяет белый цвет клетки с координатами (1, 2).
 */
TEST(desk_of_chess, NeighborCellIsWhite) {
	// Arrange
	int x = 1;
	int y = 2;

	// Act
	bool is_black = desk_of_chess(x, y);

	// Assert
	EXPECT_FALSE(is_black);
}

/**
 * @brief Проверяет, что ровно два из трёх чисел являются нечётными.
 *
 * @param a Первое целое число.
 * @param b Второе целое число.
 * @param c Третье целое число.
 * @return true, если ровно два числа нечётные, иначе false.
 */
bool two_odd_nums(int a, int b, int c) {
	int count = 0;
	if (std::abs(a % 2) == 1) ++count;
	if (std::abs(b % 2) == 1) ++count;
	if (std::abs(c % 2) == 1) ++count;
	return count == 2;
}

// ---------- two_odd_nums ----------

/**
 * @brief Проверяет наличие ровно двух нечётных чисел.
 */
TEST(two_odd_nums, ExactlyTwoOdd) {
	// Arrange
	int a = 1;
	int b = 3;
	int c = 4;

	// Act
	bool result = two_odd_nums(a, b, c);

	// Assert
	EXPECT_TRUE(result);
}

/**
 * @brief Проверяет отказ для трёх нечётных чисел.
 */
TEST(two_odd_nums, AllThreeOdd) {
	// Arrange
	int a = 1;
	int b = 3;
	int c = 5;

	// Act
	bool result = two_odd_nums(a, b, c);

	// Assert
	EXPECT_FALSE(result);
}

/**
 * @brief Проверяет подсчёт двух отрицательных нечётных чисел.
 */
TEST(two_odd_nums, TwoNegativeOdd) {
	// Arrange
	int a = -1;
	int b = -3;
	int c = 4;

	// Act
	bool result = two_odd_nums(a, b, c);

	// Assert
	EXPECT_TRUE(result);
}

/**
 * @brief Возвращает большее из двух целых чисел.
 *
 * @param num1 Первое целое число.
 * @param num2 Второе целое число.
 * @return Максимальное из двух чисел.
 */
int max_num(int num1, int num2) {
	return (num1 > num2) ? num1 : num2;
}

// ---------- max_num ----------

/**
 * @brief Проверяет выбор большего первого числа.
 */
TEST(max_num, FirstGreater) {
	// Arrange
	int num1 = 7;
	int num2 = 3;

	// Act
	int result = max_num(num1, num2);

	// Assert
	EXPECT_EQ(result, 7);
}

/**
 * @brief Проверяет выбор большего второго числа.
 */
TEST(max_num, SecondGreater) {
	// Arrange
	int num1 = 2;
	int num2 = 9;

	// Act
	int result = max_num(num1, num2);

	// Assert
	EXPECT_EQ(result, 9);
}

/**
 * @brief Проверяет максимум равных отрицательных чисел.
 */
TEST(max_num, EqualAndNegative) {
	// Arrange
	int num1 = -5;
	int num2 = -5;

	// Act
	int result = max_num(num1, num2);

	// Assert
	EXPECT_EQ(result, -5);
}

/**
 * @brief Находит порядковый номер числа, отличного от трёх равных между собой.
 *
 * @param a Первое целое число.
 * @param b Второе целое число.
 * @param c Третье целое число.
 * @param d Четвёртое целое число.
 * @pre Ровно три числа равны между собой, а четвёртое отличается от них.
 * @return Порядковый номер отличного числа (1–4).
 */
int find_diff_index(int a, int b, int c, int d) {
	if (a != b && a != c) return 1;
	if (b != a) return 2;
	if (c != a) return 3;
	return 4;
}

// ---------- find_diff_index ----------

/**
 * @brief Проверяет индекс первого отличающегося числа.
 */
TEST(find_diff_index, FirstIsDifferent) {
	// Arrange
	int a = 5;
	int b = 2;
	int c = 2;
	int d = 2;

	// Act
	int index = find_diff_index(a, b, c, d);

	// Assert
	EXPECT_EQ(index, 1);
}

/**
 * @brief Проверяет индекс третьего отличающегося числа.
 */
TEST(find_diff_index, ThirdIsDifferent) {
	// Arrange
	int a = 7;
	int b = 7;
	int c = 1;
	int d = 7;

	// Act
	int index = find_diff_index(a, b, c, d);

	// Assert
	EXPECT_EQ(index, 3);
}

/**
 * @brief Проверяет индекс четвёртого отличающегося числа.
 */
TEST(find_diff_index, LastIsDifferent) {
	// Arrange
	int a = 4;
	int b = 4;
	int c = 4;
	int d = 9;

	// Act
	int index = find_diff_index(a, b, c, d);

	// Assert
	EXPECT_EQ(index, 4);
}

/**
 * @brief Определяет, какая из точек B или C расположена ближе к точке A.
 *
 * При равных расстояниях возвращается точка B.
 *
 * @param a Координата точки A.
 * @param b Координата точки B.
 * @param c Координата точки C.
 * @return Пара: имя ближайшей точки ('B' или 'C') и её расстояние до A.
 */
std::pair<char, double> closest_to_a(double a, double b, double c) {
	double dist_b = std::abs(b - a);
	double dist_c = std::abs(c - a);
	if (dist_b <= dist_c)
		return { 'B', dist_b };
	else
		return { 'C', dist_c };
}

// ---------- closest_to_a ----------

/**
 * @brief Проверяет выбор ближайшей точки B и расстояние до неё.
 */
TEST(closest_to_a, BIsCloser) {
	// Arrange
	double a = 0;
	double b = 2;
	double c = 5;

	// Act
	auto [point, dist] = closest_to_a(a, b, c);

	// Assert
	EXPECT_EQ(point, 'B');
	EXPECT_DOUBLE_EQ(dist, 2);
}

/**
 * @brief Проверяет выбор ближайшей точки C и расстояние до неё.
 */
TEST(closest_to_a, CIsCloser) {
	// Arrange
	double a = 10;
	double b = 15;
	double c = 8;

	// Act
	auto [point, dist] = closest_to_a(a, b, c);

	// Assert
	EXPECT_EQ(point, 'C');
	EXPECT_DOUBLE_EQ(dist, 2);
}

/**
 * @brief Проверяет выбор B при равных расстояниях.
 */
TEST(closest_to_a, EqualDistancesReturnsB) {
	// Arrange
	double a = 0;
	double b = -3;
	double c = 3;

	// Act
	auto [point, dist] = closest_to_a(a, b, c);

	// Assert
	EXPECT_EQ(point, 'B');
	EXPECT_DOUBLE_EQ(dist, 3);
}

