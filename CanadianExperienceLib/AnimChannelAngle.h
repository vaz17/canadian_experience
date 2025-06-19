/**
 * @file AnimChannelAngle.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef ANIMCHANNELANGLE_H
#define ANIMCHANNELANGLE_H
#include "AnimChannel.h"


/**
 * Class for AnimChannel Angles
 */
class AnimChannelAngle : public AnimChannel {
private:
 /// The Angle of the object
 double mAngle = 0;


protected:
 /// Class that represents a keyframe
 class KeyframeAngle : public Keyframe
 {
 private:
  /// The Angle of the keyframe
  double mAngle;

  /// The channel this keyframe is associated with
  AnimChannelAngle *mChannel;

 protected:


 public:
  /// Default Constructor (Disabled)
  KeyframeAngle() = delete;
  /// Copy Constructor (Disabled)
  KeyframeAngle(const KeyframeAngle &) = delete;
  /// Assignment Operator (Disabled)
  void operator=(const KeyframeAngle &) = delete;

  /**
   * Constructor
   * @param channel The channel we are for
   * @param angle The angle for the keyframe
  */
  KeyframeAngle(AnimChannelAngle *channel, double angle) :
          Keyframe(channel), mChannel(channel), mAngle(angle) {}

  /// Use this keyframe as keyframe 1
  void UseAs1() override { mChannel->mKeyframe1 = this; }

  /// Use this keyframe as keyframe 2
  void UseAs2() override { mChannel->mKeyframe2 = this; }

  /// Use this keyframe as the angle
  void UseOnly() override { mChannel->mAngle = mAngle; }

  /**
   * Gets the angle of the object
   * @return Angle of object
   */
  double GetAngle() { return mAngle; }
 };

private:
 /// The first angle keyframe
 KeyframeAngle *mKeyframe1 = nullptr;

 /// The second angle keyframe
 KeyframeAngle *mKeyframe2 = nullptr;



public:
 /// Default Constructor
 AnimChannelAngle() = default;
 /// Copy Constructor (Disabled)
 AnimChannelAngle(const AnimChannelAngle &) = delete;
 /// Assignment Operator (Disabled)
 void operator=(const AnimChannelAngle &) = delete;

 void SetKeyframe(double angle);
 void Tween(double t);

 /**
  * Gets the angle of the object
  * @return Angle of the object
  */
 double GetAngle() const { return mAngle; };

};



#endif //ANIMCHANNELANGLE_H
