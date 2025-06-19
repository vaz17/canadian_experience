/**
 * @file AnimChannel.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef ANIMCHANNEL_H
#define ANIMCHANNEL_H


class Timeline;
/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
private:
 /// Name of AnimChannel
 std::wstring mName;
 /// Position of keyframe 1
 int mKeyframe1 = -1;
 /// Position of keyframe 2
 int mKeyframe2 = -1;

 /// The timeline object
 Timeline *mTimeline = nullptr;

protected:
 /// Default constructor
 AnimChannel() { }

 /**
  * Virtual function that tweens keyframes
  * @param t Time
  */
 virtual void Tween(double t) {};



 /// Class that represents a keyframe
 class Keyframe
 {
 private:
  /// Frame that keyframe is instantiated at
  int mFrame;
  /// The channel this keyframe is associated with
  AnimChannel *mChannel;



 protected:
  /**
   * Constructor
   * @param channel Channel we are associated with
   */
  Keyframe(AnimChannel *channel) : mChannel(channel) {}

  /**
   * Inserts a keyframe
   * @param keyframe Keyframe to be inserted
   */
  void InsertKeyFrame(std::shared_ptr<Keyframe> keyframe);
  /**
   * Tweens a keyframe
   * @param t Time
   */
  virtual void Tween(double t) { };

 public:
  /// Default Constructor (Disabled)
  Keyframe() = delete;
  /// Copy Constructor (Disabled)
  Keyframe(const Keyframe &) = delete;
  /// Assignment Operator (Disabled)
  void operator=(const Keyframe &) = delete;
  /// Destructor (virtual)
  virtual ~Keyframe() { };

  /// Virtual function to use keyframe as 1
  virtual void UseAs1() { };
  /// Virtual function to use keyframe as 2
  virtual void UseAs2() { };
  /// Virtual function to only use this keyframe
  virtual void UseOnly() { };

  /**
   * Sets the frame of the KeyFrame
   * @param frame The frame we are at
   */
  void SetFrame(int frame) { mFrame = frame; };
  /**
   * Gets the frame of the KeyFrame
   * @return The frame we are at
   */
  int GetFrame() const { return mFrame; };
 };



private:
 /// The collection of keyframes for this channel
 std::vector<std::shared_ptr<Keyframe>> mKeyframes;


public:
 /// Copy Constructor (Disabled)
 AnimChannel(const AnimChannel &) = delete;
 /// Assignment Operator (Disabled)
 void operator=(const AnimChannel &) = delete;
 /// Destructor (virtual)
 virtual ~AnimChannel() { }

 void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);;

 bool IsValid();
 void DeleteKeyframe();

 void SetFrame(int currFrame);

 /**
  * Gets name of AnimChannel
  * @return Name of AnimChannel
  */
 std::wstring GetName() { return mName; };

 /**
  * Sets name of AnimChannel
  * @param name Name of AnimChannel
  */
 void SetName(const std::wstring& name) { mName = name; };

 /**
  * Gets the Timeline that this AnimChannel is apart of
  * @return Timeline that is linked
  */
 Timeline *GetTimeline() { return mTimeline; };

 /**
  * Sets the Timeline that this AnimChannel is apart of
  * @param timeline Timeline that is linked
  */
 void SetTimeline(Timeline *timeline) { mTimeline = timeline; };





};



#endif //ANIMCHANNEL_H
