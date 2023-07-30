#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <future>
#include <string>
#include <sstream>

std::string stream(std::vector<int>::iterator begin);
void print(int& x);

template<typename It, typename T>
T par_for_each(It first, It last, T sss) {
    unsigned long size = distance(first, last);
    unsigned long max_size = 1;
    if (size <= max_size) {
        return stream(first);
    }
    else {
        It mid = first;
        std::advance(mid, size / 2);
        std::future<std::string> first_half_res = std::async(par_for_each<It, T>, first, mid, sss);
        T second_half_res = par_for_each(mid, last, sss);
        return first_half_res.get() + second_half_res;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::string sss = "sss";

    std::cout << "Вывод оригинальноого for_each: ";
    std::for_each(vec.begin(), vec.end(), print); std::cout << "\n" << std::endl;

    std::cout << "Вывод копии for_each: ";
    std::cout << par_for_each(vec.begin(), vec.end(), sss) << std::endl;
    system("Pause");
    return 0;
}

std::string stream(std::vector<int>::iterator begin) {
    std::string str = "";
    std::stringstream ss;
    ss << *begin;
    ss << " ";
    str = ss.str();
    return str;
}

void print(int& x) {
    std::cout << x << " ";
}