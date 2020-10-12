#include <iostream>
#include <random>

int main()
{
    std::default_random_engine engine;
    std::uniform_int_distribution<> distribution(0, 10000);
    const int size = 10000;
    std::cout << size << '\n';
    for (int i = 0 ; i < size; i++)
    {
        std::cout << distribution(engine) << ' ';
    }
    return 0;
}
