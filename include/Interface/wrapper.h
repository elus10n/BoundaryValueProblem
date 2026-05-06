#pragma once 

#include <vector>
#include <memory>
#include <optional>

#include "Solvers/solver_wrappers.h"

struct FrontendOutput
{
    int n; //размерность сетки
    double epsilon; //первая достигнутая погрешность, которая оказалась ниже заданной
    double x_max_deflection; //точка, в которой достигнуто максимальное отклонение
    std::vector<double> grid; //сетка
    std::optional<std::vector<double>> grid2; //двойная сетка
    std::vector<double> to_compare; //вектор, с которым надо сравнивать. В основной задаче это 2n сетка, а в тестовой - аналитическое решение
    std::vector<double> numerical; //вектор с численным решением
};

struct EpsAnalyzis
{
    int x_idx;
    double diff;
};

EpsAnalyzis get_epsilon(const std::vector<double> &num, const std::vector<double> &to_compare, TYPE type);
std::vector<double> get_grid(int n);
FrontendOutput Wrapper(std::unique_ptr<WrapperInterface> wrapper);
