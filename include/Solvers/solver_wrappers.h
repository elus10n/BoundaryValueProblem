#pragma once

#include <functional>
#include <optional>

#include "task1.h"
#include "task2.h"
#include "task3.h"
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

    WrapperInterface(TYPE type, Solver solver, std::optional<AnalyticSolver> af = std::nullopt) : type_(type), solver_(solver), analytic_func_(af) {}

    TYPE get_type() const { return type_;}

    Solver get_solver() const { return solver_;}

    std::optional<AnalyticSolver> get_af() const { return analytic_func_;}

};

class Task1Wrapper : public WrapperInterface {
public:
    Task1Wrapper() : WrapperInterface(TYPE::TEST, TASK1::solve_default_test, TASK1::solve_anal_test) {}
};

class Task2Wrapper : public WrapperInterface {
    public:
    Task2Wrapper() : WrapperInterface(TYPE::MAIN, TASK2::solve_default_main) {}
};

class Task3Wrapper : public WrapperInterface {
public:
    Task3Wrapper() : WrapperInterface(TYPE::TEST, TASK3::solve_mixed_test, TASK3::solve_anal_mixed_test) {}
};

class Task4Wrapper : public WrapperInterface {
    public:
    Task4Wrapper() : WrapperInterface(TYPE::MAIN, TASK4::solve_mixed_main) {}
};

