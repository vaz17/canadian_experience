/**
 * @file PictureFactory.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef PICTUREFACTORY_H
#define PICTUREFACTORY_H
#include <memory>

#include "Picture.h"

/**
 * A factory class that builds our picture.
 */
class PictureFactory {
private:

public:
 std::shared_ptr<Picture> Create(std::wstring imagesDir);
};



#endif //PICTUREFACTORY_H
