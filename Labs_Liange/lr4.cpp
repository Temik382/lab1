#include "pch.h"
#include <iostream>
#include <tuple>
#include <cmath>
#include <string>
#include <sstream>
#include <windows.h>


/**
 * @brief Определяет направление после двух поворотов.
 * @param c Начальное направление: 0 — север, 1 — восток, 2 — юг, 3 — запад.
 * @param n1 Первый поворот в четвертях оборота; положительное значение задаёт поворот по часовой стрелке.
 * @param n2 Второй поворот в четвертях оборота с тем же правилом знака.
 * @return Обозначение N, E, S или W; Error, если вычисленный остаток не соответствует направлению.
 */
std::string kompas(int c, int n1, int n2) {
	int cmd = (c + n1 + n2 + 4) % 4;
	std::string side;
	switch (cmd) {
	case 0:
		side = "N";
		break;
	case 1:
		side = "E";
		break;
	case 2:
		side = "S";
		break;
	case 3:
		side = "W";
		break;
	default:
		side = "Error";
	}

	return side;
}

/**
 * @brief Проверяет поворот с севера на восток.
 */
TEST(kompas, InitialNorthTurnEast) {
	// Arrange
	int c = 0;
	int n1 = 1;
	int n2 = 0;

	// Act
	std::string result = kompas(c, n1, n2);

	// Assert
	EXPECT_EQ(result, "E");
}

/**
 * @brief Проверяет два поворота с юга на север.
 */
TEST(kompas, TwoTurnsFromSouth) {
	// Arrange
	int c = 2;
	int n1 = 1;
	int n2 = 1;

	// Act
	std::string result = kompas(c, n1, n2);

	// Assert
	EXPECT_EQ(result, "N");
}

/**
 * @brief Проверяет сохранение направления после полного оборота.
 */
TEST(kompas, FullCircleReturn) {
	// Arrange
	int c = 1;
	int n1 = 2;
	int n2 = 2;

	// Act
	std::string result = kompas(c, n1, n2);

	// Assert
	EXPECT_EQ(result, "E");
}

// ==================== number_to_words ====================


/**
 * @brief Преобразует число от 1 до 999 в русскую словесную запись.
 * @param num Преобразуемое целое число.
 * @return Словесная запись (для чисел меньше 100 с ведущим пробелом) или error вне диапазона 1–999.
 * @note Устанавливает русскую локаль вызовом setlocale.
 */
std::string number_to_words(int num) {
	setlocale(LC_ALL, "Russian");
	if (num < 1 || num > 999)
	{
		return "error";
	}

	static const std::string hundreds[] = {
		"", "сто", "двести", "триста", "четыреста",
		"пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"
	};
	static const std::string teens[] = {
		"десять", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать",
		"пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"
	};
	static const std::string tens[] = {
		"", "", "двадцать", "тридцать", "сорок",
		"пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"
	};
	static const std::string ones[] = {
		"", "один", "два", "три", "четыре",
		"пять", "шесть", "семь", "восемь", "девять"
	};

	int h = num / 100;
	int t = (num / 10) % 10;
	int o = num % 10;
	std::string result = hundreds[h];

	 
	switch (t) {
		case 1:
			result += " " + teens[o];
			break;
		default:
			if (t > 1) result += " " + tens[t];
			if (o > 0) result += " " + ones[o];
	}
	return result;
}

/**
 * @brief Проверяет словесную запись числа 256.
 */
TEST(number_to_words, Number256) {
	// Arrange
	int num = 256;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "двести пятьдесят шесть");
}

/**
 * @brief Проверяет словесную запись числа 814.
 */
TEST(number_to_words, Number814) {
	
	// Arrange
	int num = 814;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "восемьсот четырнадцать"); 
}

/**
 * @brief Проверяет словесную запись числа 300.
 */
TEST(number_to_words, RoundHundred) {
	// Arrange
	int num = 300;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "триста");
}

/**
 * @brief Проверяет ошибку для числа вне диапазона 1–999.
 */
TEST(number_to_words, number_1000) {
	// Arrange
	int num = 1000;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "error");
}

// ==================== next_date ====================

/**
 * @brief Выводит следующую дату для невисокосного года в std::cout.
 * @param D День месяца.
 * @param M Номер месяца от 1 до 12.
 * @pre D и M задают существующую дату невисокосного года.
 * @note Формат вывода: день.месяц и перевод строки. После 31.12 выводится 1.1.
 * @note При M > 12 или превышении числа дней месяца выводится Error; нижние границы не проверяются.
 */
void next_date(int D, int M) {
	if (M > 12) {
		std::cout << "Error" << std::endl;
		return;
	}
	else if (M == 1 || M == 3 || M == 5 || M == 7 || M == 8 || M == 10 || M == 12) {
		if (D > 31) std::cout << "Error" << std::endl;
		if (D < 31) std::cout << D + 1 << "." << M << std::endl;
		if (D == 31 && M != 12) {
			D = 1;
			M++;
			std::cout << D << "." << M << std::endl;
		}
		else if (D == 31 && M == 12) {
			D = 1;
			M = 1;
			std::cout << D << "." << M << std::endl;
		}
		return;
	}
	switch(M) {
	case 2:
		if (D > 28) std::cout << "Error" << std::endl;
		if (D < 28) std::cout << D + 1 << "." << M << std::endl;
		if (D == 28) std::cout << 1 << "." << M + 1 << std::endl;
		break;
	default: 
		if (D > 30) std::cout << "Error" << std::endl;
		if (D < 30) std::cout << D + 1 << "." << M << std::endl;
		if (D == 30) std::cout << 1 << "." << M + 1 << std::endl;
	}
}

/**
 * @brief Проверяет следующую дату в середине января.
 */
TEST(next_date, OrdinaryDayInJanuary) {
	// Arrange
	int D = 15;
	int M = 1;
	std::ostringstream output;
	std::streambuf* old_buffer = std::cout.rdbuf(output.rdbuf());

	// Act
	next_date(D, M);
	std::cout.rdbuf(old_buffer);

	// Assert
	EXPECT_EQ(output.str(), "16.1\n");
}

/**
 * @brief Проверяет переход с 28 февраля на 1 марта.
 */
TEST(next_date, EndOfFebruary) {
	// Arrange
	int D = 28;
	int M = 2;
	std::ostringstream output;
	std::streambuf* old_buffer = std::cout.rdbuf(output.rdbuf());

	// Act
	next_date(D, M);
	std::cout.rdbuf(old_buffer);

	// Assert
	EXPECT_EQ(output.str(), "1.3\n");
}

/**
 * @brief Проверяет переход с 31 декабря на 1 января.
 */
TEST(next_date, EndOfYear) {
	// Arrange
	int D = 31;
	int M = 12;
	std::ostringstream output;
	std::streambuf* old_buffer = std::cout.rdbuf(output.rdbuf());

	// Act
	next_date(D, M);
	std::cout.rdbuf(old_buffer);

	// Assert
	EXPECT_EQ(output.str(), "1.1\n");
}

// ==================== sum_double ====================

/**
 * @brief Вычисляет сумму первых N членов гармонического ряда.
 * @param N Количество слагаемых.
 * @return Сумма 1 + 1/2 + ... + 1/N; при N <= 0 возвращается 0.
 */
double sum_double(int N) {
	double count = 0;

	for (int i = 1; i <= N; i++) {
		count += 1.0 / i;
	}

	return count;
}

/**
 * @brief Проверяет гармоническую сумму из одного слагаемого.
 */
TEST(sum_double, SingleElement) {
	// Arrange
	int N = 1;

	// Act
	double result = sum_double(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 1.0);
}

/**
 * @brief Проверяет гармоническую сумму из двух слагаемых.
 */
TEST(sum_double, TwoElements) {
	// Arrange
	int N = 2;

	// Act
	double result = sum_double(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 1.5);
}

/**
 * @brief Проверяет гармоническую сумму из четырёх слагаемых с допуском.
 */
TEST(sum_double, FourElements) {
	// Arrange
	int N = 4;

	// Act
	double result = sum_double(N);

	// Assert
	EXPECT_NEAR(result, 2.083333, 1e-5);
}

// ==================== fibnachi ====================

/**
 * @brief Выводит числа Фибоначчи в std::cout, по одному в строке.
 * @param N Количество выводимых чисел; ожидается N >= 2.
 * @note Первые две единицы выводятся всегда, в том числе при N < 2. Значения должны помещаться в int.
 */
void fibnachi(int N) {
	std::cout << "1\n1\n";
	int num1 = 1;
	int num2 = 1;
	for (int i = 3; i <= N; i++) {
		int num_n = num1 + num2;
		std::cout << num_n << std::endl;
		num1 = num2;
		num2 = num_n;
	}
}

/**
 * @brief Проверяет вывод первых двух чисел Фибоначчи.
 */
TEST(fibnachi, FirstTwoNumbers) {
	// Arrange
	int N = 2;
	testing::internal::CaptureStdout();

	// Act
	fibnachi(N);
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(output, "1\n1\n");
}

/**
 * @brief Проверяет вывод первых трёх чисел Фибоначчи.
 */
TEST(fibnachi, ThreeNumbers) {
	// Arrange
	int N = 3;
	testing::internal::CaptureStdout();

	// Act
	fibnachi(N);
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(output, "1\n1\n2\n");
}

/**
 * @brief Проверяет вывод первых пяти чисел Фибоначчи.
 */
TEST(fibnachi, FiveNumbers) {
	// Arrange
	int N = 5;
	testing::internal::CaptureStdout();

	// Act
	fibnachi(N);
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(output, "1\n1\n2\n3\n5\n");
}

// ==================== fact_19 ====================

/**
 * @brief Вычисляет факториал числа.
 * @param N Неотрицательное целое число.
 * @return Произведение чисел от 1 до N; при N <= 0 возвращается 1.
 */
double fact_19(int N) {
	double cnt = 1;
	for (int i = 1; i <= N; i++)
		cnt *= i;
	return cnt;
}

/**
 * @brief Проверяет факториал единицы.
 */
TEST(fact_19, FactorialOfOne) {
	// Arrange
	int N = 1;

	// Act
	double result = fact_19(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 1.0);
}

/**
 * @brief Проверяет факториал трёх.
 */
TEST(fact_19, FactorialOfThree) {
	// Arrange
	int N = 3;

	// Act
	double result = fact_19(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 6.0);
}

/**
 * @brief Проверяет факториал пяти.
 */
TEST(fact_19, FactorialOfFive) {
	// Arrange
	int N = 5;

	// Act
	double result = fact_19(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 120.0);
}

// ==================== double_fact_6 ====================

/**
 * @brief Вычисляет двойной факториал числа.
 * @param N Неотрицательное целое число.
 * @return Произведение N*(N-2)*...; при N <= 0 возвращается 1.
 */
double double_fact_6(int N) {
	double cnt = 1;
	if (N % 2 == 0)
	{
		while (N >= 2)
		{
			cnt *= N;
			N -= 2;
		}
	}
	else
	{
		while (N >= 1)
		{
			cnt *= N;
			N -= 2;
		}
	}
	return cnt;
}

/**
 * @brief Проверяет двойной факториал четырёх.
 */
TEST(double_fact_6, EvenNumberFour) {
	// Arrange
	int N = 4;

	// Act
	double result = double_fact_6(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 8.0);
}

/**
 * @brief Проверяет двойной факториал шести.
 */
TEST(double_fact_6, EvenNumberSix) {
	// Arrange
	int N = 6;

	// Act
	double result = double_fact_6(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 48.0);
}

/**
 * @brief Проверяет двойной факториал пяти.
 */
TEST(double_fact_6, OddNumberFive) {
	// Arrange
	int N = 5;

	// Act
	double result = double_fact_6(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 15.0);
}

// ==================== while_28 ====================

/**
 * @brief Находит индекс, при котором соседние члены последовательности отличаются не более чем на e.
 * @param e Положительная допустимая разность соседних членов.
 * @pre e > 0.
 * @return Первый индекс k >= 2 с разностью не более e для A1 = 2, A2 = 2.5, Ak = 2 + 1/A(k-1).
 */
int while_28(double e)
{
	double A1 = 2.0f;
	double A2 = 2.5f;
	int k = 2;
	while (abs(A2 - A1) > e)
	{
		double Ak = 2 + 1 / A2;
		A1 = A2;
		A2 = Ak;
		k++;
	}
	return k;
}

/**
 * @brief Проверяет остановку последовательности при допуске 0.6.
 */
TEST(while_28, LargeEpsilon) {
	// Arrange
	double e = 0.6;

	// Act
	int result = while_28(e);

	// Assert
	EXPECT_EQ(result, 2);
}

/**
 * @brief Проверяет остановку последовательности при допуске 0.2.
 */
TEST(while_28, MediumEpsilon) {
	// Arrange
	double e = 0.2;

	// Act
	int result = while_28(e);

	// Assert
	EXPECT_EQ(result, 3);
}

/**
 * @brief Проверяет остановку последовательности при допуске 0.05.
 */
TEST(while_28, SmallEpsilon) {
	// Arrange
	double e = 0.05;

	// Act
	int result = while_28(e);

	// Assert
	EXPECT_EQ(result, 4);
}

// ==================== while_10 ====================

/**
 * @brief Находит минимальное неотрицательное целое число, квадрат которого больше n.
 * @param n Число для сравнения с квадратом.
 * @return Минимальное k >= 0, удовлетворяющее k*k > n; при n < 0 возвращается 0.
 */
int while_10(int n)
{
	int k = 0;
	while (pow(k, 2) <= n) k++;
	return k;
}

/**
 * @brief Проверяет минимальный квадрат, превышающий ноль.
 */
TEST(while_10, ValueZero) {
	// Arrange
	int n = 0;

	// Act
	int result = while_10(n);

	// Assert
	EXPECT_EQ(result, 1);
}

/**
 * @brief Проверяет строгое превышение полного квадрата 9.
 */
TEST(while_10, ExactSquareNine) {
	// Arrange
	int n = 9;

	// Act
	int result = while_10(n);

	// Assert
	EXPECT_EQ(result, 4);
}

/**
 * @brief Проверяет минимальный квадрат, превышающий 10.
 */
TEST(while_10, ValueTen) {
	// Arrange
	int n = 10;

	// Act
	int result = while_10(n);

	// Assert
	EXPECT_EQ(result, 4);
}


