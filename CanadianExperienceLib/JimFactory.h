/**
 * @file JimFactory.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef JIMFACTORY_H
#define JIMFACTORY_H

#include <memory>

#include "Actor.h"

/**
 * Factory class that builds the Jim character
 */
class JimFactory {
private:

public:
 std::shared_ptr<Actor> Create(std::wstring imagesDir);
};

#endif //JIMFACTORY_H
