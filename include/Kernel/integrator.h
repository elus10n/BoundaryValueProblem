#pragma once

#include <functional>
#include "functions.h"

namespace INTEGRATOR {

    double integrate(std::function<double(double)> func, double a, double b) 
    {
        if (a > b) return 0.0;
    
        if (a < MATH::CONST::ksi && b > MATH::CONST::ksi)
            return integrate(func, a, MATH::CONST::ksi) + integrate(func, MATH::CONST::ksi, b);
        
        double mid = (a + b) / 2.0;
        return func(mid) * (b - a);
    }

    double calculate_a(std::function<double(double)> k_func, double x_prev, double x_curr) 
    {
        auto inv_k = [&](double x) { return 1.0 / k_func(x); };
        double h = x_curr - x_prev;
        double integral = integrate(inv_k, x_prev, x_curr);
        return 1.0 / (integral / h);
    }
}