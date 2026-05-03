#include "task1.h"
#include "task4.h"
#include <vector>
#include <iostream>




int main(){


    auto result1 = TASK1::solve_default_test(100);


    for (auto i : result1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    auto result4 = TASK4::solve_mixed_main(100);


    for (auto i : result4) {
        std::cout << i << " ";
    }

    return 0;
}




