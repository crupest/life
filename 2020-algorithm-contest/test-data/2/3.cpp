#include <iostream>
#include <random>
#include <cmath>

int main()
{
    std::default_random_engine engine;
    std::normal_distribution<> distribution(5000, 50);
    const int size = 5000;
    std::cout << size << ' ';
    std::cout << 6 << '\n';
    for (int i = 0 ; i < size; i++)
    {
        std::cout << std::abs((static_cast<int>(distribution(engine)) % 10000)) << ' ';
    }
    return 0;
}
