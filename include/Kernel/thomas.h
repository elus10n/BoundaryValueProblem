#pragma once 

#include <vector>

struct TridiagonalSystem 
{
    std::vector<double> a; // Нижняя диагональ (индексы 1...n)
    std::vector<double> c; // Главная диагональ (индексы 0...n)
    std::vector<double> b; // Верхняя диагональ (индексы 0...n-1)
    std::vector<double> f; // Правая часть (индексы 0...n)
    int n;                 // Количество интервалов (узлов n+1)

    TridiagonalSystem(int nodes_count);
};

std::vector<double> solve_thomas(const TridiagonalSystem& sys);
