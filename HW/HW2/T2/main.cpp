#include "cal.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cout<<"Please enter the number of integers and your target.";
    int N;
    long long D;
    cin>>N>>D;
    Calculator test(N,D);
    test.search(N);
    system("pause");
    return 0;
}