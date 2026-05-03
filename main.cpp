#include <iostream>
#include <vector>

#include "Kernel/thomas.h"


int main()
{
    std::vector<double> a{0,1,1,-1}; // Нижняя диагональ (индексы 1...n)
    std::vector<double> c{2,4,4,2}; // Главная диагональ (индексы 0...n)
    std::vector<double> b{-1,-1,-1,0}; // Верхняя диагональ (индексы 0...n-1)
    std::vector<double> f{5,10,10,5}; // Правая часть (индексы 0...n)

    TridiagonalSystem data(4);
    data.a = a;
    data.b = b;
    data.c = c;
    data.f = f;

    std::vector<double> result = solve_thomas(data);
    for(auto elem : result) 
        std::cout << elem << " ";
}
