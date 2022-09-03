#include "Shape.h"
using namespace std;

double Circle::getarea()
{
    return 3.1415926 * m_radius * m_radius;
};

double Rectangle::getarea()
{
    return m_len * m_wid;
}

double Square::getarea()
{
    return m_len * m_len;
};
