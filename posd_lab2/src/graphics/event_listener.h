#pragma once

#include "./drag_and_drop/drag_and_drop.h"
#include "./drag_and_drop/command/command.h"
#include "./drag_and_drop/mouse_position.h"
#include <map>

class EventListener
{
private:
    std::map<std::string, Command *> _callbacks;

    void _trigger(std::string eventName, double x, double y)
    {
        MousePosition::getInstance()->setPos(x, y);
        if (_callbacks.find(eventName) != _callbacks.end())
            _callbacks[eventName]->execute();
        else
            std::cout << "Event: " << eventName << "is not registered." << std::endl;
    }

public:
    EventListener() {}
    ~EventListener()
    {
        for (std::map<std::string, Command *>::iterator it = _callbacks.begin(); it != _callbacks.end(); it++)
            delete it->second;
    }

    void leftMouseMove(double x, double y)
    {
        _trigger("Left_Mouse_Move", x, y);
    }

    void leftMouseDown(double x, double y)
    {
        _trigger("Left_Mouse_Down", x, y);
    }

    void rightMouseDown(double x, double y)
    {
        _trigger("Right_Mouse_Down", x, y);
    }

    void leftMouseUp(double x, double y)
    {
        _trigger("Left_Mouse_Up", x, y);
    }

    void refresh(double x, double y)
    {
        _trigger("Refresh", x, y);
    }

    void on(std::string eventName, Command *callback)
    {
        _callbacks[eventName] = callback;
    }
};
