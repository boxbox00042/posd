#pragma once

#include "observer.h"

#include <vector>
#include <list>

class Subject
{
private:
    std::vector<Observer *> _observers;

public:
    virtual ~Subject() {}

    void attach(Observer *observer) {
        _observers.push_back(observer);
    }

    void detach(Observer *observer) {
         for(std::vector<Observer *>::const_iterator it = _observers.begin(); it != _observers.end(); ++it){
            if(*it == observer ){
                _observers.erase(it);
                return;
            }
         }
          throw std::string("Two vectors should not be parallel.");
    }

    void notify() {
        for(int i =0;i<_observers.size();i++){
            _observers[i]->update();
        }
    }

    std::vector<Observer *> getObservers() {
       return _observers;
    }

};
