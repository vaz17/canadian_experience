/**
 * @file DrawableTest.cpp
 * @author matthew vazquez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Drawable.h>

class DrawableMock : public Drawable
{
public:
 DrawableMock(const std::wstring &name) : Drawable(name) {}

 void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}
 bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableTest, Constructor)
{
 DrawableMock drawable(L"Harold");
 ASSERT_EQ(std::wstring(L"Harold"), drawable.GetName());
}

TEST(DrawableTest, position)
{
 DrawableMock drawable(L"Harold");
 ASSERT_EQ(wxPoint(0,0), drawable.GetPosition());
 drawable.SetPosition(wxPoint(100,100));
 ASSERT_EQ(wxPoint(100,100), drawable.GetPosition());
 ASSERT_NE(wxPoint(0,0), drawable.GetPosition());
}

TEST(DrawableTest, rotation)
{
 DrawableMock drawable(L"Harold");
 ASSERT_NEAR(0, drawable.GetRotation(), 0.00001);
 drawable.SetRotation(10);
 ASSERT_NEAR(10, drawable.GetRotation(), 0.00001);
}

TEST(DrawableTest, Association)
{
 DrawableMock body(L"Body");
 auto arm = std::make_shared<DrawableMock>(L"Arm");
 auto leg = std::make_shared<DrawableMock>(L"Leg");

 ASSERT_EQ(nullptr, arm->GetParent());
 ASSERT_EQ(nullptr, leg->GetParent());

 body.AddChild(arm);
 body.AddChild(leg);

 ASSERT_EQ(&body, arm->GetParent());
 ASSERT_EQ(&body, leg->GetParent());
}