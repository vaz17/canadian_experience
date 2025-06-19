/**
* @file TimelineTest.cpp
 * @author matthew vazquez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Timeline.h>

#include <AnimChannelAngle.h>

TEST(TimelineTest, numFrames)
{
    Timeline timeline;

    ASSERT_EQ(300, timeline.GetNumFrames());
    timeline.SetNumFrames(600);
    ASSERT_EQ(600, timeline.GetNumFrames());
}

TEST(TimelineTest, frameRate)
{
    Timeline timeline;

    ASSERT_EQ(30, timeline.GetFrameRate());
    timeline.SetFrameRate(60);
    ASSERT_EQ(60, timeline.GetFrameRate());
}

TEST(TimelineTest, currentTime)
{
    Timeline timeline;

    ASSERT_NEAR(0, timeline.GetCurrentTime(), 0.0001);
    timeline.SetCurrentTime(100);
    ASSERT_NEAR(100, timeline.GetCurrentTime(), 0.0001);
}


TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}