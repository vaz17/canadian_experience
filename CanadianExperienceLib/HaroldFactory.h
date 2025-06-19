/**
 * @file HaroldFactory.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef HAROLDFACTORY_H
#define HAROLDFACTORY_H
#include <memory>

#include "Actor.h"

/**
 * Factory class that builds the Harold character
 */
class HaroldFactory {
private:

public:
 std::shared_ptr<Actor> Create(std::wstring imagesDir);
};



#endif //HAROLDFACTORY_H
