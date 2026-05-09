#pragma once

#include <cmath>

namespace MATH
{
    namespace CONST
    {
        extern const double ksi;
        extern const double gamma1, gamma2, thetta1, thetta2;
        extern const double mu1, mu2;
        extern const double required_epsilon;
    }

    namespace FUNC
    {
        double function_k_main(double x);
        double function_q_main(double x);
        double function_f_main(double x);

        double function_u_anal(double x);

        extern const double k1_test, q1_test, f1_test;
        extern const double k2_test, q2_test, f2_test;

        double function_k_test(double x);
        double function_q_test(double x);
        double function_f_test(double x);
    }
}
