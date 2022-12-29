#include "./iterator_factory.h"
#include <string>

#include <string>

std::map<std::string, IteratorFactory*> IteratorFactory::_registry;

IteratorFactory* IteratorFactory::getInstance(std::string name) {
    return _registry[name];
};

void IteratorFactory::_register(std::string name, IteratorFactory* factory) {
    _registry[name] = factory;
};
