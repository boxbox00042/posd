#pragma once

#include <set>
#include <string>
#include "shape.h"

class BoundingBox
{
private:
    Point *_max;
    Point *_min;

public:
    BoundingBox(std::set<const Point *> points)
    {
        if (points.size() == 0)
            throw std::string("Point number should be greater than 0.");
        _max = calMaximumPoint(points);
        _min = calMinimumPoint(points);
    }

    Point *calMaximumPoint(const std::set<const Point *> points)
    {
        if (points.size() == 0)
            throw std::string("count should be greater than 0.");
        double maxX = -DBL_MAX;
        double maxY = -DBL_MAX;
        for (std::set<const Point *>::iterator it = points.begin(); it != points.end(); it++)
        {
            if ((*it)->x() > maxX)
                maxX = (*it)->x();
            if ((*it)->y() > maxY)
                maxY = (*it)->y();
        }
        return new Point(maxX, maxY);
    }

    Point *calMinimumPoint(const std::set<const Point *> points)
    {
        if (points.size() == 0)
            throw std::string("count should be greater than 0.");
        double minX = DBL_MAX;
        double minY = DBL_MAX;
        for (std::set<const Point *>::iterator it = points.begin(); it != points.end(); it++)
        {
            if ((*it)->x() < minX)
                minX = (*it)->x();
            if ((*it)->y() < minY)
                minY = (*it)->y();
        }
        return new Point(minX, minY);
    }

    const Point *max()
    {
        return _max;
    }

    const Point *min()
    {
        return _min;
    }

    bool collide(BoundingBox *box)
    {
        return !(this->_max->x() < box->min()->x() ||
                 this->_min->x() > box->max()->x() ||
                 this->_max->y() < box->min()->y() ||
                 this->_min->y() > box->max()->y());
    }

    double distance(BoundingBox *box)
    {
        return sqrt(
                   pow(_max->x() - box->max()->x(), 2) +
                   pow(_max->y() - box->max()->y(), 2)) +
               sqrt(
                   pow(_min->x() - box->min()->x(), 2) +
                   pow(_min->y() - box->min()->y(), 2));
    }
};