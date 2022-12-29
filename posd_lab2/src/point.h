#pragma once

#include <cmath>
#include <string>

class Point
{
private:
    double _x;
    double _y;

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

    bool operator<(const Point &pt) const
    {
        return _x < pt.x() || (_x == pt.x() && _y < pt.y());
    }

    void move(double deltaX, double deltaY)
    {
        _x += deltaX;
        _y += deltaY;
    }

    std::string info() const
    {
        char info[100];
        sprintf(info, "(%.2f, %.2f)", _x, _y);
        return info;
    }
};
