#include "Solvers/task1.h"
#include "Kernel/functions.h"
#include "Kernel/integrator.h"
#include "Kernel/thomas.h"

namespace TASK1
{
    std::vector<double> solve_default_test(int n)
    {
        const double L = 1.0;
        const double h = L / n;
        TridiagonalSystem sys(n + 1);

        sys.c[0] = 1.0f;
        sys.b[0] = 0.0f;
        sys.f[0] = MATH::CONST::mu1;
        for (int i = 1; i < n; ++i)
        {
            double x_i = i * h;
            double a_i = INTEGRATOR::calculate_a(MATH::FUNC::function_k_test, x_i - h, x_i);
            double a_next = INTEGRATOR::calculate_a(MATH::FUNC::function_k_test, x_i, x_i + h);

            double d_i = INTEGRATOR::integrate(MATH::FUNC::function_q_test, x_i - h / 2.0, x_i + h / 2.0) / h;
            double phi_i = INTEGRATOR::integrate(MATH::FUNC::function_f_test, x_i - h / 2.0, x_i + h / 2.0) / h;

            sys.a[i] = a_i / (h * h);
            sys.b[i] = a_next / (h * h);
            sys.c[i] = (a_i + a_next) / (h * h) + d_i;
            sys.f[i] = phi_i;
        }
        sys.a[n] = 0.0f;
        sys.c[n] = 1.0f;
        sys.f[n] = MATH::CONST::mu2;

        return solve_thomas(sys);
    }
}
