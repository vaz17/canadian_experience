/**
 * @file Picture.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef PICTURE_H
#define PICTURE_H
#include "Timeline.h"

class Actor;
class PictureObserver;

/**
 * The picture we are drawing.
 *
 * There will be one picture object that contains all of
 * our actors, which then contains the drawables.
 */
class Picture {
private:
 /// The picture size
 wxSize mSize = wxSize(1500, 800);

 /// The observers of this picture
 std::vector<PictureObserver *> mObservers;

 /// Vector of actors
 std::vector<std::shared_ptr<Actor>> mActors;

 /// The animation timeline
 Timeline mTimeline;


public:
 /**
 * Constructor
 */
 Picture() {};

 /// Copy Constructor (Disabled)
 Picture(const Picture &) = delete;
 /// Assignment Operator (Disabled)
 void operator=(const Picture &) = delete;

 /**
 * Get the picture size
 * @return Picture size in pixels
 */
 wxSize GetSize() {return mSize;}

 /**
  * Set the picture size
  * @param size Picture size in pixels
  */
 void SetSize(wxSize size) {mSize = size;}

 /**
 * Get a pointer to the Timeline object
 * @return Pointer to the Timeline object
 */
 Timeline *GetTimeline() {return &mTimeline;}



 void AddObserver(PictureObserver *observer);
 void RemoveObserver(PictureObserver *observer);
 void UpdateObservers();
 void AddActor(std::shared_ptr<Actor> actor);
 void Draw(std::shared_ptr<wxGraphicsContext> graphics);
 void SetAnimationTime(double time);

 /**
  * Iterator for Pictures in Actor
  */
 class ActorIterator {
 private:
  /// Private constructor for the iterator class
  typename std::vector<std::shared_ptr<Actor>>::iterator mCurrent;

 public:
  /**
   * Constructor
   * @param current Current spot
   */
  ActorIterator(typename std::vector<std::shared_ptr<Actor>>::iterator current)
      : mCurrent(current) {}

  /**
   * Dereference operator
   * @return Current object pointed at
   */
  std::shared_ptr<Actor>& operator*() { return *mCurrent; }

  /**
   * Arrow operator
   * @return Current object pointed at
   */
  std::shared_ptr<Actor>* operator->() { return &(*mCurrent); }

  /**
   * Preincrement operator
   * @return Pointer to preincrement spot
   */
  ActorIterator& operator++() {
   ++mCurrent;
   return *this;
  }

  /**
 * Postincrement operator
 * @return Pointer to postincrement spot
 */
  ActorIterator operator++(int) {
   ActorIterator temp = *this;
   ++mCurrent;
   return temp;
  }

  /**
   * Non equality operator
   * @param other Other object
   * @return True of objects are not equal
   */
  bool operator!=(const ActorIterator& other) const {
   return mCurrent != other.mCurrent;
  }

  /**
   * Equality operator
   * @param other Other object
   * @return True of objects are equal
   */
  bool operator==(const ActorIterator& other) const {
   return mCurrent == other.mCurrent;
  }
 };

 /**
  * Gets beginning of iterator
  * @return Pointer to beginning of iterator
  */
 ActorIterator begin() {
  return ActorIterator(mActors.begin());
 }

 /**
 * Gets end of iterator
 * @return Pointer to end of iterator
 */
 ActorIterator end() {
  return ActorIterator(mActors.end());
 }

};



#endif //PICTURE_H
