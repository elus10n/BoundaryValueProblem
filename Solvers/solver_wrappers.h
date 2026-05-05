#ifndef SOLVER_WRAPPERS_H
#define SOLVER_WRAPPERS_H

#include <functional>
#include <optional>

#include "task4.h"

using Solver = std::function<std::vector<double>(int)>;
using AnalyticSolver = std::function<std::vector<double>(int)>;


enum class TYPE
{
    MAIN, TEST, UNKNOWN
};

class WrapperInterface
{
    TYPE type_ = TYPE::UNKNOWN;
    Solver solver_;
    std::optional<AnalyticSolver> analytic_func_;

    public:

    WrapperInterface(TYPE type, Solver solver, std::optional<AnalyticSolver> af = std::nullopt) : type_(type), solver_(solver) {}

    TYPE get_type() const { return type_;}

    Solver get_solver() const { return solver_;}

    std::optional<AnalyticSolver> get_af() const { return analytic_func_;}

};

//каждый должен наследовать свой класс. Те, у кого ТЕСТОВАЯЯ, должны предоставить сюда функцию, которая вернет вектор с аналитическим решением по размеру сетки 3-м параметром.
class Task4Wrapper : public WrapperInterface
{
    public:
    Task4Wrapper() : WrapperInterface(TYPE::MAIN, TASK4::solve_mixed_main) {}
};

#endif