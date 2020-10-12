#include <iostream>
#include <string>
#include <vector>
#include <cassert>

enum class Op
{
    Add,
    Sub,
    Mul,
    Div
};

struct OpInfo
{
    explicit OpInfo(Op op) : op(op), count(0) {}

    Op op;
    int count; // operand count
};

int main()
{
    std::string expr;
    std::getline(std::cin, expr);

    std::vector<int> operands;
    std::vector<OpInfo> op_infos;

    for (auto c : expr)
    {
        if (c == '+')
        {
            op_infos.emplace_back(Op::Add);
        }
        else if (c == '-')
        {
            op_infos.emplace_back(Op::Sub);
        }
        else if (c == '*')
        {
            op_infos.emplace_back(Op::Mul);
        }
        else if (c == '/')
        {
            op_infos.emplace_back(Op::Div);
        }
        else if (c == '(')
        {
            if (!op_infos.empty())
                op_infos.back().count++;
        }
        else if (c >= '0' && c <= '9')
        {
            operands.push_back(c - '0');
            op_infos.back().count++;
        }
        else if (c == ')')
        {
            const auto &info = op_infos.back();
            if ((info.op == Op::Sub || info.op == Op::Div) && info.count != 2)
            {
                std::cerr << "Sub or Div Op has not 2 operands.";
                return 1;
            }

            switch (info.op)
            {
            case Op::Add:
            {
                int r = 0;
                for (int i = 0; i < info.count; i++)
                {
                    r += operands.back();
                    operands.pop_back();
                }
                operands.push_back(r);
                op_infos.pop_back();
                break;
            }
            case Op::Sub:
            {
                int a = operands.back();
                operands.pop_back();
                int b = operands.back();
                operands.pop_back();
                operands.push_back(b - a);
                op_infos.pop_back();
                break;
            }
            case Op::Mul:
            {
                int r = 1;
                for (int i = 0; i < info.count; i++)
                {
                    r *= operands.back();
                    operands.pop_back();
                }
                operands.push_back(r);
                op_infos.pop_back();
                break;
            }
            case Op::Div:
            {
                int a = operands.back();
                operands.pop_back();
                int b = operands.back();
                operands.pop_back();
                operands.push_back(b / a);
                op_infos.pop_back();
                break;
            }
            default:
                std::terminate();
            }
        }
    }

    if (operands.size() != 1)
    {
        std::cerr << "final operand count is not 1, but " << operands.size();
        return 1;
    }
    if (!op_infos.empty())
    {
        std::cerr << "final op_info is not empty";
        return 1;
    }

    std::cout << operands.front();

    return 0;
}
