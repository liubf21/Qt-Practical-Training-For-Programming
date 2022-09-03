#pragma once
#include <vector>
// 定义二叉树
typedef struct 
{
    double data = 0;
    int exp;
    int par = 0, lchild = 0, rchild = 0;
}node;

class Calculator
{
    int m_num; // 输入数字个数
    int m_res; // 所需结果
    int MAX_N; // 数组最大下标
    static std::vector<node> numbers;
    double cal(int cho, double a, double b);
    void printExp(int exp);
    void inOrder(int n, std::vector<node> numbers_tr);
public:
    Calculator(int n=4,int r=24);
    void search(int num=4, std::vector<node> numbers_=numbers); // 缺省参数值是静态绑定在静态类型成员上面
};

