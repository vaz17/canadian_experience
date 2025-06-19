/**
 * @file ImageDrawable.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef IMAGEDRAWABLE_H
#define IMAGEDRAWABLE_H
#include "Drawable.h"


/**
 * Derived from Drawable, is a class for any part of an actor
 */
class ImageDrawable : public Drawable {
private:
 /// Center of image
 wxPoint mCenter = wxPoint(0, 0);

 /// The graphics bitmap we will use
 wxGraphicsBitmap mBitmap;

protected:
 /// The image we are drawing
 std::unique_ptr<wxImage> mImage;

public:
 ImageDrawable(const std::wstring &name, const std::wstring &filename);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics);
 bool HitTest(wxPoint pos);

 /**
  * Gets center of image
  * @return Center of image
  */
 wxPoint GetCenter() { return mCenter; };
 /**
  * Sets center of image
  * @param center Center of image
  */
 void SetCenter(wxPoint center) { mCenter = center; };
};



#endif //IMAGEDRAWABLE_H
