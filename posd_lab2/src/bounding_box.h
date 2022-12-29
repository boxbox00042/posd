#pragma once

#include <set>
#include <string>
#include <cfloat>
#include "shape.h"

class BoundingBox
{
private:
    Point _max;
    Point _min;

public:
    BoundingBox(std::set<Point> points): _max(calMaximumPoint(points)), _min(calMinimumPoint(points))
    {
        if (points.size() == 0)
            throw std::string("Point number should be greater than 0.");
    }

    Point calMaximumPoint(std::set<Point> &points)
    {
        if (points.size() == 0)
            throw std::string("count should be greater than 0.");
        double maxX = -DBL_MAX;
        double maxY = -DBL_MAX;
        for (std::set<Point>::iterator it = points.begin(); it != points.end(); it++)
        {
            if ((*it).x() > maxX)
                maxX = (*it).x();
            if ((*it).y() > maxY)
                maxY = (*it).y();
        }
        return Point(maxX, maxY);
    }

    Point calMinimumPoint(std::set<Point> &points)
    {
        if (points.size() == 0)
            throw std::string("count should be greater than 0.");
        double minX = DBL_MAX;
        double minY = DBL_MAX;
        for (std::set<Point>::iterator it = points.begin(); it != points.end(); it++)
        {
            if ((*it).x() < minX)
                minX = (*it).x();
            if ((*it).y() < minY)
                minY = (*it).y();
        }
        return Point(minX, minY);
    }

    Point max()
    {
        return _max;
    }

    Point min()
    {
        return _min;
    }

    bool collide(BoundingBox *box)
    {
        return !(this->_max.x() < box->min().x() ||
                 this->_min.x() > box->max().x() ||
                 this->_max.y() < box->min().y() ||
                 this->_min.y() > box->max().y());
    }
};