#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

LARGE_INTEGER t1, t2, tc;
int m_Array1[512][512][512], m_Array2[512][512][512], m_Array3[512][512][512];

void addArray_1(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                m_Array3[i][j][k] = m_Array1[i][j][k] + m_Array2[i][j][k];
            }
        }
    }
}
void addArray_2(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int j = 0; j < n; j++)
            {
                m_Array3[i][j][k] = m_Array1[i][j][k] + m_Array2[i][j][k];
            }
        }
    }
}
void addArray_3(int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int k = 0; k < n; k++)
            {
                m_Array3[i][j][k] = m_Array1[i][j][k] + m_Array2[i][j][k];
            }
        }
    }
}
void addArray_4(int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                m_Array3[i][j][k] = m_Array1[i][j][k] + m_Array2[i][j][k];
            }
        }
    }
}
void addArray_5(int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                m_Array3[i][j][k] = m_Array1[i][j][k] + m_Array2[i][j][k];
            }
        }
    }
}
void addArray_6(int n)
{
    for (int k = 0; k < n; k++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int i = 0; i < n; i++)
            {
                m_Array3[i][j][k] = m_Array1[i][j][k] + m_Array2[i][j][k];
            }
        }
    }
}
typedef void (*LP)(int);

int main()
{

    int n = 64;
    cout<<"Please enter the value of n."<<endl;
    cin>>n;
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                m_Array1[i][j][k] = rand();
                m_Array2[i][j][k] = rand();
            }
        }
    }
    LP fun[] = {addArray_1, addArray_2, addArray_3, addArray_4, addArray_5, addArray_6};
    QueryPerformanceFrequency(&tc);
    for (int i = 0; i < 6; i++)
    {
        QueryPerformanceCounter(&t1);
        for (int j = 0; j < 3; j++)
        {
            fun[i](n);
        }
        QueryPerformanceCounter(&t2);
        cout << "Way" << i + 1 << " TimeConsume:" << ((t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart) << endl;
    }
    system("pause");
    return 0;
}