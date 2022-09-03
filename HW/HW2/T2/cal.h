#pragma once
#include <vector>

class Calculator
{
    int m_num; // 输入数字个数
    long long m_res; // 所需结果
    long long re;
    static std::vector<int> numbers;
    std::vector<int>express{0}; // 储存临时表达式
    double cal(int cho, double a, double b);
    void printExp(int exp);
public:
    Calculator(int n,long long r);
    bool search(int num, std::vector<int> numbers_=numbers);
};