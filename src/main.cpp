#include <iostream>
#include <vector>
#include <memory>

#include "include/Interface/wrapper.h"


int main()
{
    // пример для того, кто будет фронт делать. В структуре есть все необходимое
    std::unique_ptr<WrapperInterface> task4 = std::make_unique<Task4Wrapper>();
    FrontendOutput output4 = Wrapper(std::move(task4));

    for(const auto elem : output4.grid)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for(const auto elem : output4.grid2.value())
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for(const auto elem : output4.numerical)
        std::cout << elem << " ";
    std::cout << std::endl;

    std::cout << output4.epsilon << " " << output4.x_max_deflection << std::endl;
}
