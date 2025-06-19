/**
 * @file Picture.cpp
 * @author matthew vazquez
 */
 
#include "pch.h"
#include "Picture.h"

#include "Actor.h"
#include "PictureObserver.h"



/**
 * Add an observer to this picture.
 * @param observer The observer to add
 */
void Picture::AddObserver(PictureObserver* observer)
{
 mObservers.push_back(observer);
}

/**
 * Remove an observer from this picture
 * @param observer The observer to remove
 */
void Picture::RemoveObserver(PictureObserver* observer)
{
 auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
 if (loc != std::end(mObservers))
 {
  mObservers.erase(loc);
 }
}

/**
 * Update all observers to indicate the picture has changed.
 */
void Picture::UpdateObservers()
{
 for (auto observer : mObservers)
 {
  observer->UpdateObserver();
 }
}

/**
 * Adds actor to vector
 * @param actor Actor to be added
 */
void Picture::AddActor(std::shared_ptr<Actor> actor)
{
 mActors.push_back(actor);
 actor->SetPicture(this);

}

/**
 * Draws a picture
 * @param graphics Graphics content to draw on
 */
void Picture::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
 for (auto actor : mActors)
 {
  actor->Draw(graphics);
 }
}

/** Set the current animation time
*
* This forces the animation of all
* objects to the current animation location.
* @param time The new time.
*/
void Picture::SetAnimationTime(double time)
{
 mTimeline.SetCurrentTime(time);

 for (auto actor : mActors)
 {
  actor->GetKeyframe();
 }

 UpdateObservers();
}

