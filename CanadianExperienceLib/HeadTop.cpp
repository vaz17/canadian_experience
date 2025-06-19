/**
 * @file HeadTop.cpp
 * @author matthew vazquez
 */

#include "pch.h"
#include "HeadTop.h"

#include "Actor.h"
#include "Timeline.h"

/**
 * Constructor
 * @param name The drawable name
 * @param filename The filename for the image
 */
HeadTop::HeadTop(const std::wstring &name, const std::wstring &filename): ImageDrawable(name, filename)
{
}

/**
 * Draws the base class and the add ons
 * @param graphics Graphics content to draw on
 */
void HeadTop::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    // Call the base class draw function to draw the head image
    ImageDrawable::Draw(graphics);

    // Draw the eyes and eyebrows on the head
    DrawEyes(graphics);
    DrawEyebrows(graphics);
}

/**
 * Draws the eyes of the actor
 * @param graphics Graphics content to draw on
 */
void HeadTop::DrawEyes(std::shared_ptr<wxGraphicsContext> graphics) {
    // Define eye size and relative position
    float eyeWidth = 15.0f;
    float eyeHeight = 20.0f;

    graphics->SetBrush(*wxBLACK);
    graphics->SetPen(*wxBLACK);

    // Use TransformPoint to get screen coordinates for eye positions
    wxPoint eyeLeft = TransformPoint(wxPoint(40, 80));
    wxPoint eyeRight = TransformPoint(wxPoint(70, 80));

    // Draw left eye
    graphics->PushState();
    graphics->Translate(eyeLeft.x, eyeLeft.y);
    graphics->Rotate(-mPlacedR);  // Rotate to match head's rotation
    graphics->DrawEllipse(-eyeWidth / 2, -eyeHeight / 2, eyeWidth, eyeHeight);
    graphics->PopState();

    // Draw right eye
    graphics->PushState();
    graphics->Translate(eyeRight.x, eyeRight.y);
    graphics->Rotate(-mPlacedR);
    graphics->DrawEllipse(-eyeWidth / 2, -eyeHeight / 2, eyeWidth, eyeHeight);
    graphics->PopState();
}

/**
 * Draws the eyebrows of the actor
 * @param graphics Graphics content to draw on
 */
void HeadTop::DrawEyebrows(std::shared_ptr<wxGraphicsContext> graphics) {
    // Define eyebrow thickness and relative positions
    wxPen eyebrowPen(*wxBLACK, 2);
    graphics->SetPen(eyebrowPen);

    // Use TransformPoint to determine eyebrow positions
    wxPoint leftEyebrowStart = TransformPoint(wxPoint(32, 60));
    wxPoint leftEyebrowEnd = TransformPoint(wxPoint(47, 62));
    wxPoint rightEyebrowStart = TransformPoint(wxPoint(62, 63));
    wxPoint rightEyebrowEnd = TransformPoint(wxPoint(77, 60));

    // Draw left eyebrow
    graphics->StrokeLine(leftEyebrowStart.x, leftEyebrowStart.y, leftEyebrowEnd.x, leftEyebrowEnd.y);

    // Draw right eyebrow
    graphics->StrokeLine(rightEyebrowStart.x, rightEyebrowStart.y, rightEyebrowEnd.x, rightEyebrowEnd.y);
}



/** Transform a point from a location on the bitmap to
*  a location on the screen.
* @param  p Point to transform
* @returns Transformed point
*/
wxPoint HeadTop::TransformPoint(wxPoint p)
{
    // Make p relative to the image center
    p = p - GetCenter();

    // Rotate as needed and offset
    return RotatePoint(p, mPlacedR) + mPlacedPosition;
}

/**
 * Sets the keyframe
 */
void HeadTop::SetKeyframe()
{
    // Call the base class method to set the angle keyframe
    Drawable::SetKeyframe();

    // Set the keyframe for the position channel
    mChannel.SetKeyframe(GetPosition());
}

/**
 * Deletes Key Frame
 */
void HeadTop::DeleteKeyframe()
{
    Drawable::DeleteKeyframe();

    mChannel.DeleteKeyframe();
}

/**
 * Gets Key frame
 */
void HeadTop::GetKeyframe()
{
    // Call the base class method to get the angle keyframe
    Drawable::GetKeyframe();

    // Get the keyframe update for the position channel
    if (mChannel.IsValid())
    {
        SetPosition(mChannel.GetPosition());
    }
}

/**
 * Sets the timeLine
 * @param timeline Time to be set
 */
void HeadTop::SetTimeline(Timeline* timeline)
{
    // Call the base class method to add the angle channel
    Drawable::SetTimeline(timeline);

    // Add the position channel to the timeline
    timeline->AddChannel(&mChannel);
}

/**
 * Set the actor using this drawable
 * @param actor Actor using this drawable
 */
void HeadTop::SetActor(Actor *actor)
{
    Drawable::SetActor(actor);
    // Set the channel name
    mChannel.SetName(actor->GetName() + L":" + GetName());
}