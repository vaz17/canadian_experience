/**
 * @file HeadTop.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef HEADTOP_H
#define HEADTOP_H
#include "AnimChannelPosition.h"
#include "ImageDrawable.h"

/**
 * Derived from ImageDrawable, is a moveable top of a head
 */
class HeadTop : public ImageDrawable{
private:
 void DrawEyes(std::shared_ptr<wxGraphicsContext> graphics);
 void DrawEyebrows(std::shared_ptr<wxGraphicsContext> graphics);

 /// The animation channel for animating the angle of this drawable
 AnimChannelPosition mChannel;

public:
 HeadTop(const std::wstring &name, const std::wstring &filename);

 /**
  * Returns if this object is movable
  * @return True
  */
 bool IsMovable() override { return true; };

 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
 wxPoint TransformPoint(wxPoint p);
 void SetKeyframe() override;
 void DeleteKeyframe();
 void GetKeyframe() override;
 void SetTimeline(Timeline* timeline) override;
 void SetActor(Actor* actor) override;
};



#endif //HEADTOP_H
