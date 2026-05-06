#pragma once

#include <functional>
#include "functions.h"

namespace INTEGRATOR {

    double integrate(std::function<double(double)> func, double a, double b);
    double calculate_a(std::function<double(double)> k_func, double x_prev, double x_curr);

}
