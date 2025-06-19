/**
 * @file PolyDrawable.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef POLYDRAWABLE_H
#define POLYDRAWABLE_H
#include "Drawable.h"

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable{
private:
 /// The polygon color
 wxColour mColor = *wxBLACK;

 /// The array of point objects
 std::vector<wxPoint> mPoints;

 /// The transformed graphics path used
 /// to draw this polygon
 wxGraphicsPath mPath;

public:
 /// Destructor
 virtual ~PolyDrawable() {}

 /// Default constructor (disabled)
 PolyDrawable() = delete;

 /// Copy constructor (disabled)
 PolyDrawable(const PolyDrawable &) = delete;

 PolyDrawable(const std::wstring &name);

 /// Assignment operator
 void operator=(const PolyDrawable &) = delete;

 /**
  * Gets color of polygon
  * @return The color of the polygon
  */
 wxColour GetColor() const { return mColor; }
 /**
  * Sets the color of the polygon
  * @param color The new color
  */
 void SetColor(const wxColour& color) { mColor = color; }

 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

 bool HitTest(wxPoint point) override;

 void AddPoint(wxPoint point);

};



#endif //POLYDRAWABLE_H
