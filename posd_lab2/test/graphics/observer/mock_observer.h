#pragma once

#include "../../../src/graphics/observer/observer.h"

class MockObserver : public Observer
{
private:
    bool _isUpdated = false;

public:
    void update() override
    {
        _isUpdated = true;
    }

    bool isUpdated()
    {
        return _isUpdated;
    }
};
