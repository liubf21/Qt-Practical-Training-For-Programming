
//定义拥有纯虚函数的抽象类Shape
class Shape{
public:
    virtual double getarea()=0;
};
class Circle:public Shape{
private:
    double m_radius;
public:
    Circle(double r):m_radius(r){};
    double getarea();
};
class Rectangle:public Shape{
private:
    double m_len,m_wid;
public:
    Rectangle()=default;
    Rectangle(double l,double w):m_len(l),m_wid(w){};
    double getarea();
};
class Square:public Rectangle{
private:
    double m_len;
public:
    Square(double l):m_len(l){};
    double getarea();
};