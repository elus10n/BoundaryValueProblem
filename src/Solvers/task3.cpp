#include "Solvers/task3.h"
#include "Kernel/functions.h"
#include "Kernel/integrator.h"
#include "Kernel/thomas.h"

namespace TASK3
{
    std::vector<double> solve_mixed_test(int n) 
    {
        const double L = 1.0; 
        const double h = L / n;
        TridiagonalSystem sys(n + 1);

        double k0 = MATH::FUNC::function_k_test(0.0);
        
        sys.c[0] = MATH::CONST::gamma1 + k0 / h;
        sys.b[0] = k0 / h;
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
        
        sys.a[n] = kn / h;
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
    // // НОВАЯ АНАЛИТИЧЕСКАЯ ФУНКЦИЯ ДЛЯ TASK 3
    // std::vector<double> solve_anal_mixed_test(int n) 
    // {
    //     // Вектор C хранит 4 коэффициента. Вычислится 1 раз при первом запуске
    //     static std::vector<double> C; 

    //     if (C.empty()) {
    //         double k1 = MATH::FUNC::k1_test, q1 = MATH::FUNC::q1_test, f1 = MATH::FUNC::f1_test;
    //         double k2 = MATH::FUNC::k2_test, q2 = MATH::FUNC::q2_test, f2 = MATH::FUNC::f2_test;

    //         double lam1 = std::sqrt(q1 / k1), lam2 = std::sqrt(q2 / k2);
    //         double up1 = f1 / q1, up2 = f2 / q2;
    //         double xi = MATH::CONST::ksi;
    //         double g1 = MATH::CONST::gamma1, g2 = MATH::CONST::gamma2;
    //         double t1 = MATH::CONST::thetta1, t2 = MATH::CONST::thetta2;

    //         std::vector<std::vector<double>> A(4, std::vector<double>(4, 0.0));
    //         std::vector<double> B(4, 0.0);

    //         // Составляем систему 4x4
    //         A[0][0] = -k1 * lam1 + g1; A[0][1] = k1 * lam1 + g1; B[0] = t1 - g1 * up1;
    //         A[1][0] = std::exp(lam1 * xi); A[1][1] = std::exp(-lam1 * xi); A[1][2] = -std::exp(lam2 * xi); A[1][3] = -std::exp(-lam2 * xi); B[1] = up2 - up1;
    //         A[2][0] = -k1 * lam1 * std::exp(lam1 * xi); A[2][1] = k1 * lam1 * std::exp(-lam1 * xi); A[2][2] = k2 * lam2 * std::exp(lam2 * xi); A[2][3] = -k2 * lam2 * std::exp(-lam2 * xi); B[2] = 0;
    //         A[3][2] = k2 * lam2 * std::exp(lam2) + g2 * std::exp(lam2); A[3][3] = -k2 * lam2 * std::exp(-lam2) + g2 * std::exp(-lam2); B[3] = t2 - g2 * up2;

    //         // Метод Гаусса для решения системы
    //         for (int i = 0; i < 4; i++) {
    //             int maxRow = i;
    //             for (int k = i + 1; k < 4; k++) { if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) maxRow = k; }
    //             std::swap(A[i], A[maxRow]); std::swap(B[i], B[maxRow]);
    //             for (int k = i + 1; k < 4; k++) {
    //                 double c = -A[k][i] / A[i][i];
    //                 for (int j = i; j < 4; j++) A[k][j] += c * A[i][j];
    //                 B[k] += c * B[i];
    //             }
    //         }
    //         C.resize(4);
    //         for (int i = 3; i >= 0; i--) {
    //             C[i] = B[i];
    //             for (int j = i + 1; j < 4; j++) C[i] -= A[i][j] * C[j];
    //             C[i] /= A[i][i];
    //         }
    //     }

    //     // Заполняем вектор точных значений
    //     std::vector<double> anal(n + 1);
    //     double h = 1.0 / n;
    //     double lam1 = std::sqrt(MATH::FUNC::q1_test / MATH::FUNC::k1_test);
    //     double lam2 = std::sqrt(MATH::FUNC::q2_test / MATH::FUNC::k2_test);
    //     double up1 = MATH::FUNC::f1_test / MATH::FUNC::q1_test;
    //     double up2 = MATH::FUNC::f2_test / MATH::FUNC::q2_test;

    //     for (int i = 0; i <= n; ++i) {
    //         double x = i * h;
    //         if (x < MATH::CONST::ksi) {
    //             anal[i] = C[0] * std::exp(lam1 * x) + C[1] * std::exp(-lam1 * x) + up1;
    //         } else {
    //             anal[i] = C[2] * std::exp(lam2 * x) + C[3] * std::exp(-lam2 * x) + up2;
    //         }
    //     }
    //     return anal;
    // }
}