#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>

namespace MATH
{
    namespace CONST
    {
        const double ksi = 1.0 / std::sqrt(3.0); 

        const double gamma1 = 1.0;
        const double gamma2 = 1.0;
        const double thetta1 = 1.0;
        const double thetta2 = 1.0;

        const double mu1 = 2.0;
        const double mu2 = 1.0;

        const double required_epsilon = 0.5 * 1e-6;
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
        const double q1_test = 1.0 / 3.0;
        const double f1_test = (1.0 / 3.0) - 1.0;

        const double k2_test = std::exp(1.0 / 3.0);
        const double q2_test = 1.0 + 1.0 / 9.0;
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