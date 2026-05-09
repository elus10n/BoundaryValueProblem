#ifndef TASK3_H
#define TASK3_H

#include <vector>
#include <functional>
#include "../Kernel/functions.h"
#include "../Kernel/integrartor.h"
#include "../Kernel/thomas.h"

namespace TASK3
{
    std::vector<double> solve_mixed_test(int n) 
    {
        const double L = 1.0; 
        const double h = L / n;
        TridiagonalSystem sys(n + 1);

        double k0 = MATH::FUNC::function_k_test(0.0);
        
        sys.c[0] = MATH::CONST::gamma1 + k0 / h;
        sys.b[0] = -k0 / h;
        sys.f[0] = MATH::CONST::thetta1;

        for (int i = 1; i < n; ++i) 
        {
            double x_i = i * h;

            double a_i = INTEGRATOR::calculate_a(MATH::FUNC::function_k_test, x_i - h, x_i);
            double a_next = INTEGRATOR::calculate_a(MATH::FUNC::function_k_test, x_i, x_i + h);
            
            double d_i = INTEGRATOR::integrate(MATH::FUNC::function_q_test, x_i - h/2.0, x_i + h/2.0) / h;
            double phi_i = INTEGRATOR::integrate(MATH::FUNC::function_f_test, x_i - h/2.0, x_i + h/2.0) / h;
            
            sys.a[i] = a_i / (h * h);
            sys.b[i] = a_next / (h * h);
            sys.c[i] = (a_i + a_next) / (h * h) + d_i;
            sys.f[i] = phi_i;
        }

        double kn = MATH::FUNC::function_k_test(1.0);
        
        sys.a[n] = -kn / h;
        sys.c[n] = MATH::CONST::gamma2 + kn / h;
        sys.f[n] = MATH::CONST::thetta2;

        return solve_thomas(sys);
    }

    std::vector<double> solve_anal_mixed_test(int n) 
    {
        const double L = 1.0;
        const double h = L / n;
        std::vector<double> anal(n + 1);
        
        for (int i = 0; i <= n; ++i) {
            double x_i = i * h;
            anal[i] = MATH::FUNC::function_u_anal_mixed(x_i);
        }
        return anal;
    }
}

#endif