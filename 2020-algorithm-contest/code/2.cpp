#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    int size;
    std::cin >> size;
    int target;
    std::cin >> target;

    std::map<int, int> nums;

    for (int i = 0; i < size; i++)
    {
        int v;
        std::cin >> v;

        nums[v]++;
    }

    std::vector<int> counts;
    std::vector<std::vector<int>> sets;

    for (const auto &pair : nums)
    {
        auto iter = std::lower_bound(counts.cbegin(), counts.cend(), pair.second);
        if (iter != counts.cend() && *iter == pair.second)
        {
            sets[iter - counts.cbegin()].push_back(pair.first);
        }
        else
        {
            const auto offset = iter - counts.cbegin();
            counts.insert(iter, pair.second);
            sets.insert(sets.cbegin() + offset, std::vector<int>{pair.first});
        }
    }

    if (target > counts.size())
    {
        std::cout << 0;
    }
    else
    {
        const auto &set = sets[counts.size() - target];
        std::cout << set.size() << '\n';
        for (auto i : set)
            std::cout << i << ' ';
    }

    return 0;
}
