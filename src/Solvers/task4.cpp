#include "Solvers/task4.h"
#include "Kernel/functions.h"
#include "Kernel/integrator.h"
#include "Kernel/thomas.h"

namespace TASK4
{
    std::vector<double> solve_mixed_main(int n)
    {
        const double L = 1.0;
        const double h = L / n;
        TridiagonalSystem sys(n + 1);

        double a1 = INTEGRATOR::calculate_a(MATH::FUNC::function_k_main, 0.0, h);
        double d0 = INTEGRATOR::integrate(MATH::FUNC::function_q_main, 0.0, h / 2.0) / (h / 2.0);
        double phi0 = INTEGRATOR::integrate(MATH::FUNC::function_f_main, 0.0, h / 2.0) / (h / 2.0);

        sys.c[0] = (a1 / h + d0 * h / 2.0 + MATH::CONST::gamma1);
        sys.b[0] = a1 / h;
        sys.f[0] = (phi0 * h / 2.0 + MATH::CONST::thetta1);

        for (int i = 1; i < n; ++i)
        {
            double x_i = i * h;
            double a_i = INTEGRATOR::calculate_a(MATH::FUNC::function_k_main, x_i - h, x_i);
            double a_next = INTEGRATOR::calculate_a(MATH::FUNC::function_k_main, x_i, x_i + h);

            double d_i = INTEGRATOR::integrate(MATH::FUNC::function_q_main, x_i - h / 2.0, x_i + h / 2.0) / h;
            double phi_i = INTEGRATOR::integrate(MATH::FUNC::function_f_main, x_i - h / 2.0, x_i + h / 2.0) / h;

            sys.a[i] = a_i / (h * h);
            sys.b[i] = a_next / (h * h);
            sys.c[i] = (a_i + a_next) / (h * h) + d_i;
            sys.f[i] = phi_i;
        }

        double an = INTEGRATOR::calculate_a(MATH::FUNC::function_k_main, L - h, L);
        double dn = INTEGRATOR::integrate(MATH::FUNC::function_q_main, L - h / 2.0, L) / (h / 2.0);
        double phin = INTEGRATOR::integrate(MATH::FUNC::function_f_main, L - h / 2.0, L) / (h / 2.0);

        sys.a[n] = an / h;
        sys.c[n] = (an / h + dn * h / 2.0 + MATH::CONST::gamma2);
        sys.f[n] = (phin * h / 2.0 + MATH::CONST::thetta2);

        return solve_thomas(sys);
    }
}
