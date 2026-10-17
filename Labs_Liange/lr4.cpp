#include "pch.h"
#include <iostream>
#include <tuple>
#include <cmath>
#include <string>
#include <windows.h>


/// @brief 
/// @param c 
/// @param n1 
/// @param n2 
/// @return 
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

TEST(number_to_words, Number256) {
	// Arrange
	int num = 256;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "двести пятьдесят шесть");
}

TEST(number_to_words, Number814) {
	
	// Arrange
	int num = 814;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "восемьсот четырнадцать"); 
}

TEST(number_to_words, RoundHundred) {
	// Arrange
	int num = 300;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "триста");
}

TEST(number_to_words, number_1000) {
	// Arrange
	int num = 1000;

	// Act
	std::string result = number_to_words(num);

	// Assert
	EXPECT_EQ(result, "error");
}

// ==================== next_date ====================

void next_date(int D, int M) {
	if (M > 12) {
		std::cout << "Error" << std::endl;
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

TEST(next_date, OrdinaryDayInJanuary) {
	// Arrange
	int D = 15;
	int M = 1;
	testing::internal::CaptureStdout();

	// Act
	next_date(D, M);
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(output, "16.1\n");
}

TEST(next_date, EndOfFebruary) {
	// Arrange
	int D = 28;
	int M = 2;
	testing::internal::CaptureStdout();

	// Act
	next_date(D, M);
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(output, "1.3\n");
}

TEST(next_date, EndOfYear) {
	// Arrange
	int D = 31;
	int M = 12;
	testing::internal::CaptureStdout();

	// Act
	next_date(D, M);
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(output, "1.1\n");
}

// ==================== sum_double ====================

double sum_double(int N) {
	double count = 0;

	for (int i = 1; i <= N; i++) {
		count += 1.0 / i;
	}

	return count;
}

TEST(sum_double, SingleElement) {
	// Arrange
	int N = 1;

	// Act
	double result = sum_double(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(sum_double, TwoElements) {
	// Arrange
	int N = 2;

	// Act
	double result = sum_double(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST(sum_double, FourElements) {
	// Arrange
	int N = 4;

	// Act
	double result = sum_double(N);

	// Assert
	EXPECT_NEAR(result, 2.083333, 1e-5);
}

// ==================== fibnachi ====================

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

double fact_19(int N) {
	double cnt = 1;
	for (int i = 1; i <= N; i++)
		cnt *= i;
	return cnt;
}

TEST(fact_19, FactorialOfOne) {
	// Arrange
	int N = 1;

	// Act
	double result = fact_19(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(fact_19, FactorialOfThree) {
	// Arrange
	int N = 3;

	// Act
	double result = fact_19(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 6.0);
}

TEST(fact_19, FactorialOfFive) {
	// Arrange
	int N = 5;

	// Act
	double result = fact_19(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 120.0);
}

// ==================== double_fact_6 ====================

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

TEST(double_fact_6, EvenNumberFour) {
	// Arrange
	int N = 4;

	// Act
	double result = double_fact_6(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 8.0);
}

TEST(double_fact_6, EvenNumberSix) {
	// Arrange
	int N = 6;

	// Act
	double result = double_fact_6(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 48.0);
}

TEST(double_fact_6, OddNumberFive) {
	// Arrange
	int N = 5;

	// Act
	double result = double_fact_6(N);

	// Assert
	EXPECT_DOUBLE_EQ(result, 15.0);
}

// ==================== while_28 ====================

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

TEST(while_28, LargeEpsilon) {
	// Arrange
	double e = 0.6;

	// Act
	int result = while_28(e);

	// Assert
	EXPECT_EQ(result, 2);
}

TEST(while_28, MediumEpsilon) {
	// Arrange
	double e = 0.2;

	// Act
	int result = while_28(e);

	// Assert
	EXPECT_EQ(result, 3);
}

TEST(while_28, SmallEpsilon) {
	// Arrange
	double e = 0.05;

	// Act
	int result = while_28(e);

	// Assert
	EXPECT_EQ(result, 4);
}

// ==================== while_10 ====================

int while_10(int n)
{
	int k = 0;
	while (pow(k, 2) <= n) k++;
	return k;
}

TEST(while_10, ValueZero) {
	// Arrange
	int n = 0;

	// Act
	int result = while_10(n);

	// Assert
	EXPECT_EQ(result, 1);
}

TEST(while_10, ExactSquareNine) {
	// Arrange
	int n = 9;

	// Act
	int result = while_10(n);

	// Assert
	EXPECT_EQ(result, 4);
}

TEST(while_10, ValueTen) {
	// Arrange
	int n = 10;

	// Act
	int result = while_10(n);

	// Assert
	EXPECT_EQ(result, 4);
}


