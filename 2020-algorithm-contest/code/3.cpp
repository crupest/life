#include <iostream>

int main()
{
    int length, numRows;
    std::cin >> length >> numRows;

    if (numRows == 1)
    {
        for (int i = 1; i <= length; i++)
            std::cout << i << ' ';
        return 0;
    }

    const int count_per_group = numRows * 2 - 2;
    for (int row = 0; row < numRows; row++)
    {
        if (row == 0)
        {
            for (int p = 0; p < length; p += count_per_group)
                std::cout << p + 1 << ' ';
        }
        else if (row == numRows - 1)
        {
            for (int p = row; p < length; p += count_per_group)
                std::cout << p + 1 << ' ';
        }
        else
        {
            bool former = true;
            const auto former_gap = count_per_group - row * 2;
            const auto latter_gap = count_per_group - former_gap;
            for (int p = row; p < length; p += (former ? former_gap : latter_gap), former = !former)
                std::cout << p + 1 << ' ';
        }
    }
    return 0;
}
