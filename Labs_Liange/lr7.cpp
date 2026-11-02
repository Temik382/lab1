#include <iostream>
#include "pch.h"
#include <list>
#include <iterator>
#include <deque>
#include <algorithm>
#include <vector>


/// @brief 
void STL3Alg_4() {
    std::list<int> L = { 1, 2, -1, 3, 4, -2, 5, 6};

    int cnt_odd = std::count_if(
        L.begin(),
        L.end(),
        [](int x) {
            return x < 0;
        }
    );

    auto it = std::find_if(
        L.begin(),
        L.end(),
        [](int x) {
            return x < 0;
        }
    );

    auto second_it = std::find_if(
        std::next(it),
        L.end(),
        [](int x) {
            return x < 0;
        }
    );

    switch (cnt_odd) {
    case 0:
        break;
    case 1:
        L.erase(++it, L.end());
        break;
    case 2:
        L.erase(++it, second_it);
    }


    //for (auto res_l = L.begin(); res_l != L.end(); ++res_l) {
    //    std::cout << *res_l << " ";
    //}
}

/// @brief 
    
void STL3Alg_26() {
    std::list<int> nums = { 1, -2, 3, -4, 4, 6, 7, 8 };

    auto middle_nums = nums.begin();
    std::advance(middle_nums, nums.size() / 2);
    std::list<int> reverse_middle_nums;
    for (--middle_nums; middle_nums != nums.begin(); --middle_nums) {
        reverse_middle_nums.push_back(*middle_nums);
    }
    reverse_middle_nums.push_back(*nums.begin());

    std::replace_copy_if(
        reverse_middle_nums.begin(),
        reverse_middle_nums.end(),
        std::back_inserter(nums),
        [](int x) {
            return (x < 0);
        },
        0
    );

    for (int x : nums) {
        std::cout << x << " ";
    }
}

int main() {
	STL3Alg_26();
}