#include <iostream>
#include <set>

int main()
{
    int size;
    std::cin >> size;
    std::set<int> s;
    int v;
    for (int i = 0; i< size; i++)
    {
        std::cin >> v;
        s.insert(v);
    }

    for (auto value : s)
    {
        std::cout << value << ' ';
    }

    return 0;
}
