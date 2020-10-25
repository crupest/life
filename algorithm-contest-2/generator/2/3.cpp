#include <iostream>
#include <random>

using std::cout;

int main() {
    std::default_random_engine engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution(1, 5000);
    const int SIZE = 5000;
    cout << SIZE << '\n';
    for (int i = 0; i < SIZE; i++) {
        cout << distribution(engine) << ' ';
    }
    return 0;
}
