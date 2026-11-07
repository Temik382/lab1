#include "pch.h"
#include <list>
#include <iterator>
#include <deque>
#include <algorithm>

/**
 * @brief Удаляет элементы после одного отрицательного числа или между двумя.
 * @param L Исходный список, содержащий не более двух отрицательных чисел.
 * @return Изменённый список; сами отрицательные числа сохраняются.
 */
std::list<int> STL3Alg_4(std::list<int> L) {
    auto first = std::find_if(L.begin(), 
        L.end(), 
        [](int x) {
            return x < 0;
        });
    if (first == L.end()) {
        return L;
    }
    auto second = std::find_if(std::next(first), 
        L.end(), 
        [](int x) { 
            return x < 0; 
        });
    L.erase(std::next(first), second);
    return L;
}

/// @brief Проверяет удаление элементов между двумя отрицательными числами.
TEST(STL3Alg_4, TwoNegativeNumbers) {
    // Arrange
    std::list<int> L = { 1, -2, 3, -4, 5 };
    std::list<int> expected = { 1, -2, -4, 5 };

    // Act
    std::list<int> result = STL3Alg_4(L);

    // Assert
    EXPECT_EQ(result, expected);
}

/// @brief Проверяет удаление элементов после одного отрицательного числа.
TEST(STL3Alg_4, OneNegativeNumber) {
    // Arrange
    std::list<int> L = { 1, -2, 3, 4 };
    std::list<int> expected = { 1, -2 };

    // Act
    std::list<int> result = STL3Alg_4(L);

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Добавляет в конец списка перевёрнутую первую половину, заменяя в копии отрицательные числа нулями.
 * @param nums Исходный список с чётным количеством элементов.
 * @return Список с добавленными элементами.
 */
std::list<int> STL3Alg_26(std::list<int> nums) {
    auto middle = nums.begin();
    std::advance(middle, nums.size() / 2);
    std::list<int> first_half(nums.begin(), middle);
    std::replace_copy_if(
        first_half.rbegin(), 
        first_half.rend(), 
        std::back_inserter(nums),
        [](int x) 
        { 
            return x < 0; 
        }, 
        0);
    return nums;
}

/// @brief Проверяет добавление первой половины списка в обратном порядке.
TEST(STL3Alg_26, PositiveNumbers) {
    // Arrange
    std::list<int> nums = { 1, 2, 3, 4 };
    std::list<int> expected = { 1, 2, 3, 4, 2, 1 };

    // Act
    std::list<int> result = STL3Alg_26(nums);

    // Assert
    EXPECT_EQ(result, expected);
}

/// @brief Проверяет замену отрицательного числа нулём в добавленной части списка.
TEST(STL3Alg_26, NegativeNumber) {
    // Arrange
    std::list<int> nums = { 1, -2, 3, 4 };
    std::list<int> expected = { 1, -2, 3, 4, 0, 1 };

    // Act
    std::list<int> result = STL3Alg_26(nums);

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Добавляет в конец дека перевёрнутую первую половину, заменяя в копии отрицательные числа нулями.
 * @param D Исходный дек с чётным количеством элементов.
 * @return Дек с добавленными элементами.
 */
std::deque<int> STL3Alg_27(std::deque<int> D) {
    std::deque<int> first_half(D.begin(), D.begin() + D.size() / 2);
    std::replace_copy_if(
        first_half.rbegin(), 
        first_half.rend(), 
        std::back_inserter(D),
        [](int x) { 
            return x < 0; 
        },
        0);
    return D;
}

/// @brief Проверяет добавление первой половины дека в обратном порядке.
TEST(STL3Alg_27, PositiveNumbers) {
    // Arrange
    std::deque<int> D = { 1, 2, 3, 4 };
    std::deque<int> expected = { 1, 2, 3, 4, 2, 1 };

    // Act
    std::deque<int> result = STL3Alg_27(D);

    // Assert
    EXPECT_EQ(result, expected);
}

/// @brief Проверяет замену отрицательного числа нулём в добавленной части дека.
TEST(STL3Alg_27, NegativeNumber) {
    // Arrange
    std::deque<int> D = { -1, 2, 3, 4 };
    std::deque<int> expected = { -1, 2, 3, 4, 2, 0 };

    // Act
    std::deque<int> result = STL3Alg_27(D);

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Добавляет в начало дека копию с одним последним элементом каждой группы одного знака.
 * @param D Исходный дек; соседние нули также считаются одной группой.
 * @return Дек с сокращённой копией перед исходными элементами.
 */
std::deque<int> STL3Alg_33(std::deque<int> D) {
    std::deque<int> original(D);
    std::unique_copy(
        original.rbegin(), original.rend(), std::front_inserter(D),
        [](int a, int b) {
            return (a > 0 && b > 0) || (a < 0 && b < 0) || (a == 0 && b == 0);
        });
    return D;
}

/// @brief Проверяет сокращение групп положительных и отрицательных чисел.
TEST(STL3Alg_33, SameSignGroups) {
    // Arrange
    std::deque<int> D = { 1, 2, -3, -4 };
    std::deque<int> expected = { 2, -4, 1, 2, -3, -4 };

    // Act
    std::deque<int> result = STL3Alg_33(D);

    // Assert
    EXPECT_EQ(result, expected);
}

/// @brief Проверяет сокращение группы нулей до одного нуля.
TEST(STL3Alg_33, ZeroGroup) {
    // Arrange
    std::deque<int> D = { 1, 0, 0, -2 };
    std::deque<int> expected = { 1, 0, -2, 1, 0, 0, -2 };

    // Act
    std::deque<int> result = STL3Alg_33(D);

    // Assert
    EXPECT_EQ(result, expected);
}

/**
 * @brief Запускает тесты Google Test.
 * @param argc Количество аргументов командной строки.
 * @param argv Аргументы командной строки.
 * @return 0, если все тесты прошли, иначе код ошибки.
 */
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
