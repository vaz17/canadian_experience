/**
 * @file AnimChannelPosition.cpp
 * @author matthew vazquez
 */

#include "pch.h"
#include "AnimChannelPosition.h"

/**
 * Set a keyframe
 *
 * This function allocates a new keyframe and sends it to
 * AnimChannel, which will insert it into the collection of keyframes.
 * @param Position Position for the keyframe.
 */
void AnimChannelPosition::SetKeyframe(wxPoint Position)
{
 // Create a keyframe of the appropriate type
 // Telling it this channel and the Position
 auto keyframe = std::make_shared<KeyframePosition>(this, Position);

 // Insert it into the collection
 InsertKeyframe(keyframe);
}

/**
 * Tweens between the two keyframes
 * @param t Time we are at
 */
void AnimChannelPosition::Tween(double t)
{
 wxPoint a = mKeyframe1->GetPosition();
 wxPoint b = mKeyframe2->GetPosition();
 mPosition = wxPoint(int(a.x + t * (b.x - a.x)),
                        int(a.y + t * (b.y - a.y)));
}