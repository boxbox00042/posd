#pragma once

#include "../../../../src/graphics/drag_and_drop/command/command.h"

class MockCommand : public Command
{
private:
    bool _isExecuteCalled = false;
    bool _isUndoCalled = false;

public:
    MockCommand(){};
    void execute() override
    {
        _isExecuteCalled = true;
    }
    void undo() override
    {
        _isUndoCalled = true;
    }
    bool isExecuteCalled() const
    {
        return _isExecuteCalled;
    }
    bool isUndoCalled() const
    {
        return _isUndoCalled;
    }
};