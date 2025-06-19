/**
 * @file PictureFactory.cpp
 * @author matthew vazquez
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "ImageDrawable.h"
#include "JimFactory.h"

class Picture;

using namespace std;

/**
 * Factory method to create a new picture.
 * @param imagesDir Directory that contains the images for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring imagesDir)
{
 shared_ptr<Picture> picture = make_shared<Picture>();

 // Create the background and add it
 auto background = make_shared<Actor>(L"Background");
 background->SetClickable(false);
 background->SetPosition(wxPoint(0, 0));
 auto backgroundI =
         make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
 background->AddDrawable(backgroundI);
 background->SetRoot(backgroundI);
 picture->AddActor(background);

 // Create and add Harold
 HaroldFactory haroldFactory;
 auto harold = haroldFactory.Create(imagesDir);

 // This is where Harold will start out.
 harold->SetPosition(wxPoint(300, 500));
 picture->AddActor(harold);

 // Create and add Harold
 JimFactory jimFactory;
 auto jim = jimFactory.Create(imagesDir);

 // This is where Harold will start out.
 jim->SetPosition(wxPoint(500, 500));
 picture->AddActor(jim);

 return picture;
}