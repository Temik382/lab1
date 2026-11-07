#include <iostream>
#include "pch.h"
#include <list>
#include <iterator>
#include <deque>
#include <numeric>

/**
 * @brief Читает целые числа и выводит их в прямом и обратном порядке.
 * @details Заполняет список числами из std::cin до конца ввода или ошибки чтения.
 * Выводит элементы через пробел в std::cout, разделяя два порядка переводом строки.
 */
void STL2Seq_2() {
    // Заполнение списка через конструктор и итераторы ввода
    std::list<int> L{
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>()
    };

    // Вывод в исходном порядке
    std::copy(
        L.begin(),
        L.end(),
        std::ostream_iterator<int>(std::cout, " ")
    );

    std::cout << '\n';

    // Вывод в обратном порядке
    std::copy(
        L.rbegin(),
        L.rend(),
        std::ostream_iterator<int>(std::cout, " ")
    );
}


/**
 * @brief Переносит первую половину дека в начало списка.
 * @details Копирует первые три элемента дека {1, 2, 3, 4, 5, 6}
 * в начало списка {10, 20, 30}, затем удаляет их из дека.
 * @note Контейнеры локальные; результат не возвращается и не выводится.
 */
void STL2Seq23() {
    std::list<int> first_arr = { 10, 20, 30 }; // Любые значения
    std::deque<int> d_arr = { 1, 2, 3, 4, 5, 6 }; // Любое четное количество значений для дека
    auto middle = d_arr.begin() + d_arr.size() / 2;

    first_arr.insert(first_arr.begin(), d_arr.begin(), middle);
    d_arr.erase(d_arr.begin(), middle);

    auto it = first_arr.begin();

    //for (it; it != first_arr.end(); it++) {
    //    std::cout << *it << " ";
    //}

    //std::cout << "\n";

    //for (int i = 0; i < d_arr.size(); i++) {
    //    std::cout << d_arr[i] << " ";
    //}
}


/**
 * @brief Перемещает первую половину второго списка в начало первого.
 * @details С помощью splice переносит элементы 1 и 2 из списка {1, 2, 3, 4}
 * в начало списка {10, 20, 30}, не копируя элементы.
 * @note Контейнеры локальные; результат не возвращается и не выводится.
 */
void STL2Seq25() {
    std::list<int> L1 = { 10, 20, 30 };
    std::list<int> L2 = { 1, 2, 3, 4 };

    auto middle_L2 = L2.begin();
    std::advance(middle_L2, L2.size() / 2);

    L1.splice(L1.begin(), L2, L2.begin(), middle_L2);

    //auto it = L1.begin();
    //for (it; it != L1.end(); ++it) {
    //    std::cout << *it << " ";
    //}
}


/**
 * @brief Обменивает вторые половины двух списков.
 * @details С помощью splice преобразует списки {10, 20, 30, 40} и
 * {1, 2, 3, 4, 5, 6} в {10, 20, 4, 5, 6} и {1, 2, 3, 30, 40}.
 * @note Контейнеры локальные; результат не возвращается и не выводится.
 */
void STL2Seq26() {
    std::list<int> L1 = { 10, 20, 30, 40 };
    std::list<int> L2 = { 1, 2, 3, 4, 5, 6 };

    auto middle_L1 = L1.begin();
    std::advance(middle_L1, L1.size() / 2);

    auto middle_L2 = L2.begin();
    std::advance(middle_L2, L2.size() / 2);

    std::list<int> temp_middle_L1;
    std::list<int> temp_middle_L2;

    temp_middle_L1.splice(
        temp_middle_L1.begin(),
        L1,
        middle_L1,
        L1.end()
    );

    temp_middle_L2.splice(
        temp_middle_L2.begin(),
        L2,
        middle_L2,
        L2.end()
    );

    L1.splice(L1.end(), temp_middle_L2);
    L2.splice(L2.end(), temp_middle_L1);

    //for (auto it = L1.begin(); it != L1.end(); ++it) {
    //    std::cout << *it << " ";
    //}

    //std::cout << "\n";

    //for (auto it = L2.begin(); it != L2.end(); ++it) {
    //    std::cout << *it << " ";
    //}
}
