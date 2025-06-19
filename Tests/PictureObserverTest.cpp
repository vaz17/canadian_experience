/**
 * @file PictureObserverTest.cpp
 * @author matthew vazquez
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <PictureObserver.h>
#include <Picture.h>

class PictureObserverMock : public PictureObserver
{
public:
 PictureObserverMock() : PictureObserver() {}

 bool mUpdated = false;

 void UpdateObserver() override { mUpdated = true; }

};

TEST(PictureObserverTest, Construct) {
 PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver) {
 // Allocate a Picture object
 auto picture = std::make_shared<Picture>();

 // Create a mock observer object
 PictureObserverMock observer;

 // And set it for the observer:
 observer.SetPicture(picture);

 picture->UpdateObservers();

 ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserverTest, GetPicture) {
 // Allocate a Picture object
 auto picture = std::make_shared<Picture>();

 // Create a mock observer object
 PictureObserverMock observer;

 // And set it for the observer:
 observer.SetPicture(picture);

 ASSERT_TRUE(observer.GetPicture() == picture);
}

TEST(PictureObserverTest, TwoObservers) {
 // Allocate a Picture object
 auto picture = std::make_shared<Picture>();

 // Create a mock observer object
 PictureObserverMock observer1;

 // Create a mock observer object
 PictureObserverMock observer2;

 // And set it for the observer:
 observer1.SetPicture(picture);

 // And set it for the observer:
 observer2.SetPicture(picture);

 picture->UpdateObservers();

 ASSERT_TRUE(observer1.mUpdated);
 ASSERT_TRUE(observer2.mUpdated);
}

TEST(PictureObserverTest, RemoveObserver) {
 // Allocate a Picture object
 auto picture = std::make_shared<Picture>();

 // Create a mock observer object
 PictureObserverMock observer1;

 // Create a mock observer object
 PictureObserverMock observer2;

 // And set it for the observer:
 observer1.SetPicture(picture);

 // And set it for the observer:
 observer2.SetPicture(picture);

 picture->RemoveObserver(&observer2);
 picture->UpdateObservers();

 ASSERT_TRUE(observer1.mUpdated);
}