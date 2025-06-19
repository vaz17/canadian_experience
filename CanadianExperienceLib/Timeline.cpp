/**
* @file Timeline.cpp
 * @author matthew vazquez
 */

#include "pch.h"
#include "Timeline.h"

#include "AnimChannel.h"

/**
* Constructor
*/
Timeline::Timeline()
{
}

/**
 * Adds channel into timeline
 * @param channel Channel to be added
 */
void Timeline::AddChannel(AnimChannel* channel)
{
 mChannels.push_back(channel);
 channel->SetTimeline(this);
}

/**
 * Sets the current time
 *
 * Ensures all of the channels are
 * valid for that point in time.
 * @param t The new time to set
 */
void Timeline::SetCurrentTime(double t)
{
 // Set the time
 mCurrentTime = t;

 for (auto channel : mChannels)
 {
  channel->SetFrame(GetCurrentFrame());
 }
}