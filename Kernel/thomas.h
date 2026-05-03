#ifndef THOMAS_H
#define THOMAS_H

#include <vector>
#include <stdexcept>
struct TridiagonalSystem 
{
    std::vector<double> a; // Нижняя диагональ (индексы 1...n)
    std::vector<double> c; // Главная диагональ (индексы 0...n)
    std::vector<double> b; // Верхняя диагональ (индексы 0...n-1)
    std::vector<double> f; // Правая часть (индексы 0...n)
    int n;                 // Количество интервалов (узлов n+1)

    TridiagonalSystem(int nodes_count) :  a(nodes_count), c(nodes_count), b(nodes_count), f(nodes_count), n(nodes_count - 1) {}
};

std::vector<double> solve_thomas(const TridiagonalSystem& sys)
{
    int n = sys.n;
    std::vector<double> alpha(n + 1, 0.0);
    std::vector<double> beta(n + 1, 0.0);
    std::vector<double> v(n + 1, 0.0);

    alpha[1] = sys.b[0] / sys.c[0];
    beta[1] = sys.f[0] / sys.c[0];

    for (int i = 1; i < n; ++i) 
    {
        double denominator = sys.c[i] - sys.a[i] * alpha[i];
        if (denominator == 0) throw std::runtime_error("Division by zero in Thomas algorithm");
        
        alpha[i + 1] = sys.b[i] / denominator;
        beta[i + 1] = (sys.f[i] + sys.a[i] * beta[i]) / denominator;
    }

    v[n] = (sys.f[n] + sys.a[n] * beta[n]) / (sys.c[n] - sys.a[n] * alpha[n]);

    for (int i = n - 1; i >= 0; --i)
        v[i] = alpha[i + 1] * v[i + 1] + beta[i + 1];

    return v;
}


#endif