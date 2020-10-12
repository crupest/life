#include <iostream>
#include <random>
#include <set>
#include <algorithm>

struct Point
{
    int x;
    int y;
};

bool operator<(const Point &left, const Point &right)
{
    return left.x == right.x ? left.y < right.y : left.x < right.x;
}

int main()
{
    std::default_random_engine engine{39};
    const int size = 20;
    const int b_size = 50;
    std::uniform_int_distribution<> distribution(0, size - 1);
    std::cout << size << ' ' << size << ' ' << b_size << '\n';

    std::set<Point> b;

    while (b.size() < b_size)
    {
        int x = distribution(engine);
        int y = distribution(engine);

        if (x == 0 && y == 0)
            continue;
        if (x == size - 1 && y == size - 1)
            continue;

        b.insert({x, y});
    }

    std::vector<Point> bb(b.cbegin(), b.cend());

    std::shuffle(bb.begin(), bb.end(), engine);

    for (const auto &p : bb)
    {
        std::cout << p.x << ' ' << p.y << '\n';
    }

    return 0;
}
