#ifndef WRAPPER_H
#define WRAPPER_H

#include <vector>
#include <memory>
#include <iostream>

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

EpsAnalyzis get_epsilon(const std::vector<double> &num, const std::vector<double> &to_compare, TYPE type)
{
    double max_diff = 0.0;
    int max_idx = -1;
    if(type == TYPE::MAIN)
    {
        for(int i = 0, j = 0 ; i < num.size() && j < to_compare.size(); i++, j+=2)
        {
            double diff = std::abs(num[i] - to_compare[j]);
            if(diff > max_diff)
            {
                max_diff = diff;
                max_idx = i;
            }
        }
    }
    else if(type == TYPE::TEST)
    {
        for(int i = 0; i < num.size(); i++)
        {
            double diff = std::abs(num[i] - to_compare[i]);
            if(diff > max_diff)
            {
                max_diff = diff;
                max_idx = i;
            }
        }
    }
    return {max_idx,max_diff};
}

std::vector<double> get_grid(int n)
{
    std::vector<double> output(n + 1);
    double step = 1.0/static_cast<double>(n);

    for(int i = 0;i <= n;i++)    
        output[i] = step*i;

    return output;
}

FrontendOutput Wrapper(std::unique_ptr<WrapperInterface> wrapper)
{

    std::vector<double> numerical;
    std::vector<double> to_compare;

    int n = 10;
    double curr_epsilon = 1;
    int max_defl_idx = -1;

    TYPE type = wrapper->get_type();
    Solver solver = wrapper->get_solver();

    if(type == TYPE::MAIN)
    {
        while(true)
        {
            std::cout << n << std::endl;
            std::cout << curr_epsilon << std::endl;
            numerical = solver(n);
            to_compare = solver(2*n);
            auto eps_analyzis = get_epsilon(numerical, to_compare, type);
            curr_epsilon = eps_analyzis.diff;

            if(curr_epsilon > MATH::CONST::required_epsilon) 
            {
                n *= 2;
                continue;
            }

            max_defl_idx = eps_analyzis.x_idx;
            break;
        }
    }
    else if(type == TYPE::TEST)
    {
        while(curr_epsilon > MATH::CONST::required_epsilon)
        {
            AnalyticSolver analytic_func = wrapper->get_af().value();

            numerical = solver(n);
            to_compare = analytic_func(n);
            auto eps_analyzis = get_epsilon(numerical, to_compare, type);
            curr_epsilon = eps_analyzis.diff;

            if(curr_epsilon > MATH::CONST::required_epsilon) 
            {
                n *= 2;
                continue;
            };

            max_defl_idx = eps_analyzis.x_idx;
            break;
        }
    }

    std::vector<double> grid = get_grid(n);
    double max_defl_point = grid[max_defl_idx];
    std::optional<std::vector<double>> grid2 = (type == TYPE::MAIN) ? std::make_optional(get_grid(2*n)) : std::nullopt;

    FrontendOutput output{n, curr_epsilon, max_defl_point, grid, grid2, to_compare, numerical};
    return output;
}

#endif 