#include "cal.h"
#include <iostream>
#include <vector>
using namespace std;

vector<int> Calculator::numbers;

Calculator::Calculator(int n, long long r)
{
    m_num = n;
    m_res = r;
    re = -1;
    numbers.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> numbers[i];
    }
}

// 定义计算
double Calculator::cal(int cho, double a, double b)
{
    switch (cho)
    {
    case 0:
        return a + b;
    case 1:
        return a * b;
    }
}
// 定义计算对应的输出符号
void Calculator::printExp(int exp)
{
    switch (-exp)
    {
    case 0:
        cout << "+";
        return;
    case 1:
        cout << "*";
        return;
    default:
        cout << exp;
        return;
    }
}

bool Calculator::search(int num, vector<int> numbers_)
{
    if (num == 0) // 退栈
    {
        if (abs(express[0] - m_res) < 0.01)
        {
            for (auto x : express)
            {
                if (x != m_res)
                    printExp(x);
            }
            cout << endl;
            return true;
        }
        else if (express[0] > m_res && (re < 0 || express[0] < re))
        {
            re = express[0];
        }
    }
    else
    {
        vector<int> numbers_tr;
        for (int i = 1; i <= num; i++)
        {
            if (num == m_num)
            {
                numbers_tr = numbers_;
                express[0] = numbers_tr[i];
                express.push_back(numbers_tr[i]);
                numbers_tr.erase(numbers_tr.begin() + i);
                if (search(num - 1, numbers_tr))
                    return true;
                else
                {
                    cout << "No" << endl
                         << re << endl;
                    return false;
                }
            }
            else
            {
                for (int cho = 0; cho < 2; cho++)
                {
                    numbers_tr = numbers_;
                    int temp = express[0];
                    express[0] = cal(cho, express[0], numbers_tr[i]);
                    express.push_back(-cho);
                    express.push_back(numbers_tr[i]);
                    numbers_tr.erase(numbers_tr.begin() + i);
                    if (search(num - 1, numbers_tr))
                        return true;
                    express[0] = temp;
                    express.pop_back();
                    express.pop_back();
                }
            }
        }
    }
    return false;
}