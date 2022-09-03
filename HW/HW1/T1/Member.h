#include<string>
#include<ostream>
#include<map>

// .h文件中不要出现using namespace 
class Member{
private:
    std::string m_name;
    int m_age;
public:
    Member(std::string name="?",int age=0):
        m_name(name),m_age(age){};
    friend std::ostream& operator << (std::ostream& out,const Member src);
    friend class MemberList;
};

class MemberList{
private:
    std::map<std::string,int> m_list;
public:
    MemberList(Member* mem,int num);
    int& operator [](std::string name);
};