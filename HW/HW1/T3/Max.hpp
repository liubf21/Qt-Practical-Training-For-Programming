//在hpp文件中编写类模板
#pragma once
using namespace std;

template<typename T>
T Max(T a,T b){
    return a>b?a:b;
}