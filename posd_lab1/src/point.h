#pragma once

#include <cmath>

class Point
{
private:
    const double _x;
    const double _y;

public:
    Point(double x, double y) : _x(x), _y(y) {}
    ~Point() {}

    double x() const
    {
        return _x;
    }

    double y() const
    {
        return _y;
    }

    bool operator==(const Point &pt) const
    {
        return (fabs(_x - pt.x()) < 0.001) && (fabs(_y - pt.y()) < 0.001);
    }

    std::string info() const
    {
        char info[100];
        sprintf(info, "(%.2f, %.2f)", _x, _y);
        return info;
    }
};
