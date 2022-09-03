#include"Member.h"
using namespace std;

ostream& operator<<(ostream& out,const Member src){
    out<<src.m_name<<"'s age is "<<src.m_age;
    return out;
}

MemberList::MemberList(Member* mem,int num){
    for(int i=0;i<num;i++){
        m_list[mem[i].m_name]=mem[i].m_age;
    }
}

int& MemberList::operator[](string name){
    return m_list[name];
}