#include "pch.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <random>
#include <ctime>
#include <cstdlib>


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


TEST(Series15, check_0) {
	// Arrange
	int check_num = 0;

	// Act
	int res = series_15(check_num);

	// Array
	EXPECT_EQ(res, 1);
}

TEST(series_15, check_101) {
	// Act
	int check_num = 101;

	// Arrange
	int res = series_15(check_num);

	// Array
	EXPECT_EQ(res, 0);
}


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

TEST(Series29, BadNK) {
	// Arrange
	int n = -3;
	int k = 12;

	// Act 
	int res = series_29(n, k);

	// Array
	EXPECT_EQ(res, 0);
}

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

TEST(series_13, CheckEvenSum) {
	// Arrange
	int remainder = 0;

	// Act
	int res = series_13();

	// Array
	EXPECT_EQ(res % 2, remainder);
}



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

TEST(series_19, CheckSingleElement) {
	// Arrange
	int n = 1;

	// Act
	int res = series_19(n);

	// Assert
	EXPECT_EQ(res, 0);
}

TEST(series_19, CheckTwoElements) {
	// Arrange
	int n = 2;

	// Act
	int res = series_19(n);

	// Assert
	EXPECT_GE(res, 0);
	EXPECT_LE(res, 1);
}
