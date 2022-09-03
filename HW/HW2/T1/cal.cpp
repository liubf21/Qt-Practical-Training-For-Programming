#include "cal.h"
#include <iostream>
#include <vector>
using namespace std;

std::vector<node> Calculator::numbers;

Calculator::Calculator(int n,int r){
    m_num=n;
    m_res=r;
    MAX_N=2*m_num-1;
    cout << "Please input four integers between 1 and 13:";
    numbers.resize(2*n);
    for (int i = 1; i <= n; i++)
    {
        cin >> numbers[i].data;
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
        return a - b;
    case 2:
        return a * b;
    case 3:
        return a / b;
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
        cout << "-";
        return;
    case 2:
        cout << "*";
        return;
    case 3:
        cout << "/";
        return;
    }
}

// 定义二叉树的中序遍历，用于输出最终表达式
void Calculator::inOrder(int n, vector<node> numbers_tr)
{
    if (numbers_tr[n].lchild == 0)
    {
        // 如果是父亲的左孩子，输出(
        if (n == numbers_tr[numbers_tr[n].par].lchild) 
        {
            cout << "(" << numbers_tr[n].data;
        }
        else
        {
            cout << numbers_tr[n].data << ")";
        }
    }
    else
    {
        inOrder(numbers_tr[n].lchild, numbers_tr);
        printExp(numbers_tr[n].exp);
        inOrder(numbers_tr[n].rchild, numbers_tr);
    }
}

void Calculator::search(int num, vector<node> numbers_)
{
    if (num == 1) // 退栈
    {
        if (abs(numbers_[MAX_N].data - 24) < 0.01)
        {
            inOrder(MAX_N, numbers_);
            // 测试输出
            // cout << "~";
            // for (auto x : numbers_)
                // cout << x.data << " ";
            cout << endl;
        }
    }
    else
    {
        for (int i = 1; i <= MAX_N; i++)
        {
            for (int j = 1; j <= MAX_N; j++)
            {
                if (j == i || numbers_[i].data == 0 || numbers_[j].data == 0 ||
                    numbers_[i].par != 0 || numbers_[j].par != 0)
                    continue;
                vector<node> numbers_tr = numbers_;
                numbers_tr[i].par = numbers_tr[j].par = 9 - num;
                numbers_tr[MAX_N+2 - num].lchild = i;
                numbers_tr[MAX_N+2 - num].rchild = j;
                for (int cho = 0; cho < 4; cho++)
                {
                    numbers_tr[MAX_N+2 - num].exp = -cho;
                    numbers_tr[MAX_N+2 - num].data = cal(cho, numbers_tr[i].data, numbers_tr[j].data);
                    search(num - 1, numbers_tr);
                }
            }
        }
    }
}