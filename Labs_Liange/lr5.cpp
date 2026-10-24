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

int main() {
	STL1Iter_7();
}