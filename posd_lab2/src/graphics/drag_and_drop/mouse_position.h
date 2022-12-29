#pragma once

class MousePosition
{
private:
    static MousePosition *_instance;
    MousePosition() {}
    double _x, _y;

public:
    ~MousePosition() {}

    static MousePosition *getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = new MousePosition();
        }
        return _instance;
    }

    void setPos(double x, double y)
    {
        _x = x;
        _y = y;
    }

    double getX()
    {
        return _x;
    }

    double getY()
    {
        return _y;
    }
};

MousePosition *MousePosition::_instance;
