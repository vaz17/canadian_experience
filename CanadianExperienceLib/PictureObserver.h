/**
 * @file PictureObserver.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef PICTUREOBSERVER_H
#define PICTUREOBSERVER_H

class Picture;
/**
 * Observer base class for a picture.
 *
 * This class implements the base class functionality for
 * an observer in the observer pattern.
 */
class PictureObserver {
private:
 /// Picture we are observing
 std::shared_ptr<Picture> mPicture;


public:
 virtual ~PictureObserver();
 void SetPicture(std::shared_ptr<Picture> picture);

 /// Copy Constructor (Disabled)
 PictureObserver(const PictureObserver &) = delete;
 /// Assignment Operator (Disabled)
 void operator=(const PictureObserver &) = delete;

 /**
  * Gets picture
  * @return Picture object
  */
 std::shared_ptr<Picture> GetPicture() { return mPicture; }

 /// This function is called to update any observers
 virtual void UpdateObserver() = 0;

protected:
 /// Constructor
 PictureObserver() {}

};



#endif //PICTUREOBSERVER_H
