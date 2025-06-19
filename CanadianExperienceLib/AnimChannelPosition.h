/**
 * @file AnimChannelPosition.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef ANIMCHANNELPOSITION_H
#define ANIMCHANNELPOSITION_H
#include "AnimChannel.h"


/**
 * Class for AnimChannel Positions
 */
class AnimChannelPosition : public AnimChannel {
private:
 /// Position of object
 wxPoint mPosition = wxPoint(0,0);


protected:
 /// Class that represents a keyframe
 class KeyframePosition : public Keyframe
 {
 private:
  /// Position of object
  wxPoint mPosition;

  /// The channel this keyframe is associated with
  AnimChannelPosition *mChannel;

 protected:


 public:
  /// Default Constructor (Disabled)
  KeyframePosition() = delete;
  /// Copy Constructor (Disabled)
  KeyframePosition(const KeyframePosition &) = delete;
  /// Assignment Operator (Disabled)
  void operator=(const KeyframePosition &) = delete;

  /**
   * Constructor
   * @param channel The channel we are for
   * @param Position The Position for the keyframe
  */
  KeyframePosition(AnimChannelPosition *channel, wxPoint Position) :
          Keyframe(channel), mChannel(channel), mPosition(Position) {}

  /// Use this keyframe as keyframe 1
  void UseAs1() override { mChannel->mKeyframe1 = this; }

  /// Use this keyframe as keyframe 2
  void UseAs2() override { mChannel->mKeyframe2 = this; }

  /// Use this keyframe as the Position
  void UseOnly() override { mChannel->mPosition = mPosition; }

  /**
   * Gets Position of the object
   * @return Position of object
   */
  wxPoint GetPosition() { return mPosition; }
 };

private:
 /// The first Position keyframe
 KeyframePosition *mKeyframe1 = nullptr;

 /// The second Position keyframe
 KeyframePosition *mKeyframe2 = nullptr;



public:
 /// Default Constructor
 AnimChannelPosition() = default;
 /// Copy Constructor (Disabled)
 AnimChannelPosition(const AnimChannelPosition &) = delete;
 /// Assignment Operator (Disabled)
 void operator=(const AnimChannelPosition &) = delete;

 void SetKeyframe(wxPoint Position);
 void Tween(double t);

 /**
  * Gets position of Object
  * @return Position of Object
  */
 wxPoint GetPosition() const { return mPosition; };

};



#endif //ANIMCHANNELPOSITION_H
