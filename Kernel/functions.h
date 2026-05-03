#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

namespace MATH
{
    namespace CONST
    {
        const double ksi = 0.57735; // 1/sqrt(3)

        const double gamma1 = 1.0;
        const double gamma2 = 1.0;
        const double thetta1 = 1.0;
        const double thetta2 = 1.0;

        const double mu1 = 2.0;
        const double mu2 = 1.0;
    }

    namespace FUNC
    {
        double function_k_main(double x)
        {
            if(x < CONST::ksi) return 1.0;
            else return exp(pow(x,2));
        }

        double function_q_main(double x)
        {
            if(x < CONST::ksi) return pow(x,2);
            else return 1.0 + pow(x,4);
        }

        double function_f_main(double x)
        {
            if(x < CONST::ksi) return pow(x,2) - 1.0;
            else return 1.0;
        }


        const double k1_test = 1.0;
        const double q1_test = 0.33333;
        const double f1_test = - 0.66666;

        const double k2_test = 1.39561;
        const double q2_test = 1.11111;
        const double f2_test = 1.0;

        double function_k_test(double x) 
        {
            return (x < CONST::ksi) ? k1_test : k2_test;
        }

        double function_q_test(double x) 
        {
            return (x < CONST::ksi) ? q1_test : q2_test;
        }

        double function_f_test(double x) 
        {
            return (x < CONST::ksi) ? f1_test : f2_test;
        }
    }
}

#endif