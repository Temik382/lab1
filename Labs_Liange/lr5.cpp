#include "pch.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>


/**
 * @brief Ищет первый элемент случайной последовательности, превышающий k.
 * @param k Порог для сравнения.
 * @return Позиция элемента, начиная с 1, или 0, если подходящего элемента нет.
 * @note Создаёт от 1 до 10 чисел в диапазоне 1–100 и переинициализирует генератор текущим временем.
 */
int series_15(int k) {
	srand(time(NULL));
	int size = (rand() % 10) + 1;

	std::vector<int> nums;
	std::vector<int>::iterator it;
	for (int i = 0; i < size; ++i) {
		nums.push_back((rand() % 100) + 1);
	}

	int pos = 1;
	for (it = nums.begin(); it != nums.end(); ++it) {
		if (*it == 0) {
			break;
		}
		else if (*it > k) {
			return pos;
		}

		++pos;
	}

	return 0;
}


/**
 * @brief Проверяет, что первый случайный элемент превышает ноль.
 */
TEST(Series15, check_0) {
	// Arrange
	int check_num = 0;

	// Act
	int res = series_15(check_num);

	// Array
	EXPECT_EQ(res, 1);
}

/**
 * @brief Проверяет отсутствие случайного элемента, превышающего 101.
 */
TEST(series_15, check_101) {
	// Act
	int check_num = 101;

	// Arrange
	int res = series_15(check_num);

	// Array
	EXPECT_EQ(res, 0);
}


/**
 * @brief Возвращает сумму элементов первой сформированной случайной последовательности.
 * @param k Запрошенное количество последовательностей; должно быть положительным.
 * @param n Количество элементов в последовательности.
 * @return Сумма n случайных чисел от 1 до 100; при k <= 0 или n <= 0 возвращается 0.
 * @note Из-за возврата внутри цикла обрабатывается только первая последовательность. Генератор инициализируется текущим временем.
 */
int series_29(int k, int n) {
	srand(time(NULL));

	if (k <= 0 || n <= 0)
		return 0;
	else {
		for (int i = 0; i < k; ++i) {
			std::vector<int> nums;
			for (int i = 0; i < n; ++i) {
				nums.push_back((rand() % 100) + 1);
			}
			std::vector<int>::iterator it;
			int count = 0;

			for (it = nums.begin(); it != nums.end(); ++it) {
				count += *it;
			}

			return count;
		}
	}
}

/**
 * @brief Проверяет нулевой результат при неположительном количестве последовательностей.
 */
TEST(Series29, BadNK) {
	// Arrange
	int n = -3;
	int k = 12;

	// Act 
	int res = series_29(n, k);

	// Array
	EXPECT_EQ(res, 0);
}

/**
 * @brief Суммирует чётные элементы случайной последовательности.
 * @return Сумма чётных чисел среди 1–10 случайных элементов со значениями от 1 до 100.
 * @note Переинициализирует генератор случайных чисел текущим временем.
 */
int series_13() {
	srand(time(NULL));

	int size = rand() % 10 + 1;
	std::vector<int> nums;
	for (int i = 0; i < size; ++i) {
		nums.push_back(rand() % 100 + 1);
	}

	int sum = 0;

	std::vector<int>::iterator it;
	for (it = nums.begin(); it != nums.end(); ++it) {
		if (*it > 0 && *it % 2 == 0) {
			sum += *it;
		}
		
	}


	return sum;
}

/**
 * @brief Проверяет диапазон суммы чётных случайных элементов.
 */
TEST(series_13, CheckSumRange) {
	// Arrange
	int min_sum = 0;
	int max_sum = 1000;

	// Act
	int res = series_13();

	// Array
	EXPECT_GE(res, min_sum);
	EXPECT_LE(res, max_sum);
}

/**
 * @brief Проверяет чётность суммы чётных элементов.
 */
TEST(series_13, CheckEvenSum) {
	// Arrange
	int remainder = 0;

	// Act
	int res = series_13();

	// Array
	EXPECT_EQ(res % 2, remainder);
}



/**
 * @brief Выводит элементы случайной последовательности, меньшие предыдущего, и считает их.
 * @param n Количество случайных чисел от 1 до 100.
 * @return Количество найденных элементов; при n <= 1 возвращается 0.
 * @note Каждый найденный элемент выводится в std::cout на отдельной строке. Генератор инициализируется текущим временем.
 */
int series_19(int n) {
	if (n <= 1)
		return 0;
	else {
		srand(time(NULL));
		int size = n;
		std::vector<int> nums;

		for (int i = 0; i < size; ++i) {
			nums.push_back(rand() % 100 + 1);
		}

		std::vector<int>::iterator it;
		int k = 0;
		for (it = nums.begin() + 1; it != nums.end(); ++it) {
			if (*it < *(it - 1)) {
				std::cout << *it << std::endl;
				k++;
			}
		}

		return k;
	}
}

/**
 * @brief Проверяет отсутствие сравнений в последовательности из одного элемента.
 */
TEST(series_19, CheckSingleElement) {
	// Arrange
	int n = 1;

	// Act
	int res = series_19(n);

	// Assert
	EXPECT_EQ(res, 0);
}

/**
 * @brief Проверяет диапазон количества убываний для двух элементов.
 */
TEST(series_19, CheckTwoElements) {
	// Arrange
	int n = 2;

	// Act
	int res = series_19(n);

	// Assert
	EXPECT_GE(res, 0);
	EXPECT_LE(res, 1);
}
