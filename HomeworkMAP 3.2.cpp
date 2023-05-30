#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <future>

void print(int& x);
void my_for_each(std::vector<int>::iterator begin, std::vector<int>::iterator end, void this_print(int&));
void my_for_each2(int& size1, const int& size2, std::vector<int>::iterator& begin, void this_print(int&));
void my_for_each3(std::vector<int>::iterator begin, std::promise<int> prom);

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Вывод оригинальноого for_each: ";
    std::for_each(vec.begin(), vec.end(), print);

    std::cout << std::endl;
    std::cout << "Вывод копии for_each: ";
    my_for_each(vec.begin(), vec.end(), print);
}

void my_for_each(std::vector<int>::iterator begin, std::vector<int>::iterator end, void this_print(int&)) {
    int null = 0;
    int size1 = 0, size2 = 0;
    int full_size = end - begin;
    size1 = (end - begin) / 3;
    if ((end - begin) % 3 == 0) {
        size2 = size1 * 2;
    }
    else {
        size2 = size1 * 2 + 1;
    }
    my_for_each2(null, size1, begin, this_print);
    my_for_each2(size1, size2, begin, this_print);
    my_for_each2(size2, full_size, begin, this_print);
}

void my_for_each2(int& size1, const int& size2, std::vector<int>::iterator& begin, void this_print(int&)) {
    std::promise<int> promise_res1; std::future<int> future_res1 = promise_res1.get_future();
    std::future<void> task1 = std::async(my_for_each3, begin, std::move(promise_res1));
    future_res1.wait(); int output = future_res1.get();
    this_print(output);
    size1++; begin++;
    if (size1 != size2) {
        return my_for_each2(size1, size2, begin, this_print);
    }
    return;
}

void my_for_each3(std::vector<int>::iterator begin, std::promise<int> prom) {
    prom.set_value(*begin);
}

void print(int& x) {
    std::cout << x << " ";
}