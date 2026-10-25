#include "pch.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include "CppUnitTest.h"

/**
 * @brief Записывает последовательность целых чисел в Name.txt, заменяя нули на десяти.
 * @return 0 при успешном завершении операции.
 * @post Файл Name.txt содержит последовательность 10 4 5 6 10 1 10.
 */
int STL1Iter_15() {
	std::ofstream file("Name.txt");

	std::vector<int> nums = { 0, 4, 5, 6, 0, 1, 0 };
	std::replace_copy(
		nums.begin(),
		nums.end(),
		std::ostream_iterator<int>(file, "  "),
		0,
		10
	);

	return 0;
}

/**
 * @brief Проверяет замену нулей на десять при записи последовательности.
 */
TEST(STL1Iter_15, ReplacesZeroes) {
	// Arrange
	// Act
	int result = STL1Iter_15();
	std::ifstream file("Name.txt");
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Assert
	EXPECT_EQ(result, 0);
	EXPECT_EQ(contents, "10  4  5  6  10  1  10  ");
}

/**
 * @brief Проверяет создание выходного файла при записи пустой логики функции.
 */
TEST(STL1Iter_15, CreatesExpectedFile) {
	// Arrange
	// Act
	STL1Iter_15();
	std::ifstream file("Name.txt");
	int first = 0;
	file >> first;

	// Assert
	EXPECT_TRUE(file.good() || file.eof());
	EXPECT_EQ(first, 10);
}

/**
 * @brief Читает целые числа из Name.txt и выводит их по одному в строке.
 * @return 0 после завершения чтения.
 * @pre Name.txt содержит последовательность целых чисел.
 */
int STL1Iter_5() {
	std::ifstream file("Name.txt");
	std::vector<int> nums;

	std::copy(
		std::istream_iterator<int>(file),
		std::istream_iterator<int>(),
		std::back_inserter(nums)
	);

	for (int number : nums) {
		std::cout << number << '\n';
	}

	return 0;
}

/**
 * @brief Проверяет построчный вывод чисел, прочитанных из Name.txt.
 */
TEST(STL1Iter_5, PrintsNumbersLineByLine) {
	// Arrange
	std::ofstream file("Name.txt");
	file << "10 20 30";
	file.close();
	testing::internal::CaptureStdout();

	// Act
	int result = STL1Iter_5();
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(result, 0);
	EXPECT_EQ(output, "10\n20\n30\n");
}

/**
 * @brief Проверяет чтение одного числа из Name.txt.
 */
TEST(STL1Iter_5, PrintsSingleNumber) {
	// Arrange
	std::ofstream file("Name.txt");
	file << "42";
	file.close();
	testing::internal::CaptureStdout();

	// Act
	STL1Iter_5();
	std::string output = testing::internal::GetCapturedStdout();

	// Assert
	EXPECT_EQ(output, "42\n");
}

/**
 * @brief Копирует из Name1.txt в Name2.txt все числа, кроме нулей.
 * @return 0 после завершения копирования.
 * @pre Name1.txt содержит последовательность целых чисел.
 * @post Name2.txt содержит ненулевые числа исходной последовательности, по одному в строке.
 */
int STL1Iter_7() {
	std::ifstream input("Name1.txt");
	std::ofstream output("Name2.txt");

	std::remove_copy(
		std::istream_iterator<int>(input),
		std::istream_iterator<int>(),
		std::ostream_iterator<int>(output, "\n"),
		0
	);

	return 0;
}

/**
 * @brief Проверяет удаление нулей из входного файла.
 */
TEST(STL1Iter_7, RemovesZeroes) {
	// Arrange
	std::ofstream input("Name1.txt");
	input << "0 4 0 5";
	input.close();

	// Act
	int result = STL1Iter_7();
	std::ifstream output("Name2.txt");
	std::string contents((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());

	// Assert
	EXPECT_EQ(result, 0);
	EXPECT_EQ(contents, "4\n5\n");
}

/**
 * @brief Проверяет копирование последовательности без нулей.
 */
TEST(STL1Iter_7, CopiesNonZeroSequence) {
	std::ofstream input("Name1.txt");
	input << "1 2 3";
	input.close();

	STL1Iter_7();
	std::ifstream output("Name2.txt");
	std::string contents((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());

	EXPECT_EQ(contents, "1\n2\n3\n");
}

/**
 * @brief Копирует из Name1.txt в Name2.txt все ненулевые числа с помощью итераторов.
 * @return 0 после завершения копирования.
 * @pre Name1.txt содержит последовательность целых чисел.
 * @post Name2.txt содержит ненулевые числа исходной последовательности, по одному в строке.
 */
int STL1Iter_11() {
	std::ifstream input("Name1.txt");
	std::ofstream output("Name2.txt");

	std::istream_iterator<int> in(input);
	std::ostream_iterator<int> out(output, "\n");

	for (in; in != std::istream_iterator<int>(); in++)
	{
		if (*in != 0) {
			*out++ = *in;
		}
	}

	return 0;
}

/**
 * @brief Проверяет удаление нулей при ручном проходе итераторами.
 */
TEST(STL1Iter_11, RemovesZeroesWithIterators) {
	std::ofstream input("Name1.txt");
	input << "0 7 0 8";
	input.close();

	int result = STL1Iter_11();
	std::ifstream output("Name2.txt");
	std::string contents((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());

	EXPECT_EQ(result, 0);
	EXPECT_EQ(contents, "7\n8\n");
}

/**
 * @brief Проверяет сохранение всех ненулевых чисел при ручном проходе.
 */
TEST(STL1Iter_11, PreservesNonZeroValues) {
	std::ofstream input("Name1.txt");
	input << "3 6 9";
	input.close();

	STL1Iter_11();
	std::ifstream output("Name2.txt");
	std::string contents((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());

	EXPECT_EQ(contents, "3\n6\n9\n");
}
