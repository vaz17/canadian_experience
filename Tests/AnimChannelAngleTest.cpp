/**
 * @file AnimChannelAngleTest.cpp
 * @author matthew vazquez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <AnimChannelAngle.h>

TEST(AnimChannelAngleTest, Constructor)
{
 AnimChannelAngle angle;
 angle.SetName(L"Harold");
 ASSERT_EQ(angle.GetName(), L"Harold");

}

