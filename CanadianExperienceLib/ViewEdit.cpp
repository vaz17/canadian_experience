/**
 * @file ViewEdit.cpp
 * @author Charles B. Owen
 */
#include "pch.h"

#include <wx/dcbuffer.h>

#include "ViewEdit.h"

#include <wx/xrc/xmlres.h>

#include "Actor.h"
#include "Drawable.h"
#include "Picture.h"

using namespace std;

/// A scaling factor, converts mouse motion to rotation in radians
const double RotationScaling = 0.02;


/**
 * Constructor
 * @param parent Pointer to wxFrame object, the main frame for the application
 */
ViewEdit::ViewEdit(wxFrame* parent) : wxScrolledCanvas(parent, wxID_ANY)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewEdit::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewEdit::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewEdit::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewEdit::OnMouseMove, this);


    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewEdit::OnEditMove, this, XRCID("EditMove"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewEdit::OnEditRotate, this, XRCID("EditRotate"));
    parent->Bind(wxEVT_UPDATE_UI, &ViewEdit::OnUpdateEditMove, this, XRCID("EditMove"));
    parent->Bind(wxEVT_UPDATE_UI, &ViewEdit::OnUpdateEditRotate, this, XRCID("EditRotate"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewEdit::SetKeyFrame, this, XRCID("SetKeyFrame"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewEdit::DeleteKeyFrame, this, XRCID("DeleteKeyFrame"));

}




/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewEdit::OnPaint(wxPaintEvent& event)
{
    auto size = GetPicture()->GetSize();
    SetVirtualSize(size.GetWidth(), size.GetHeight());
    SetScrollRate(1, 1);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    // Additional drawing code here
    GetPicture()->Draw(graphics);
}

/**
 * Changes mode to move
 * @param event Event
 */
void ViewEdit::OnEditMove(wxCommandEvent &event)
{
    mMode = Mode::Move;
}

/**
 * Changes mode to rotate
 * @param event Event
 */
void ViewEdit::OnEditRotate(wxCommandEvent &event)
{
    mMode = Mode::Rotate;
}

/**
 * Keeps edit rotate move
 * @param event Event
 */
void ViewEdit::OnUpdateEditMove(wxUpdateUIEvent &event)
{
    event.Check(mMode == Mode::Move);
}

/**
 * Keeps edit rotate updated
 * @param event Event
 */
void ViewEdit::OnUpdateEditRotate(wxUpdateUIEvent &event)
{
    event.Check(mMode == Mode::Rotate);
}

/**
 * Handle the left mouse button down event
 * @param event Event
 */
void ViewEdit::OnLeftDown(wxMouseEvent &event)
{
    mLastMouse = CalcUnscrolledPosition(event.GetPosition());
    GetPicture()->UpdateObservers();
    auto click = CalcUnscrolledPosition(event.GetPosition());
    mLastMouse = click;

    //
    // Did we hit anything?
    //

    std::shared_ptr<Actor> hitActor;
    std::shared_ptr<Drawable> hitDrawable;
    for (auto actor : *GetPicture())
    {
        // Note: We do not exit when we get the first hit, since
        // we are looking at these in drawing order. Instead, we
        // keep the last hit.
        std::shared_ptr<Drawable> drawable =
                actor->HitTest(wxPoint(click.x, click.y));
        if (drawable != nullptr)
        {
            hitActor = actor;
            hitDrawable = drawable;
        }
    }

    // If we hit something determine what we do with it based on the
    // current mode.
    if (hitActor != nullptr)
    {
        mSelectedActor = hitActor;
        mSelectedDrawable = hitDrawable;
    }
}

/**
* Handle the left mouse button up event
* @param event Event
*/
void ViewEdit::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event Event
*/
void ViewEdit::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    wxPoint newMouse(click.x, click.y);
    wxPoint delta = newMouse - mLastMouse;
    mLastMouse = newMouse;

    if (event.LeftIsDown())
    {
        switch (mMode)
        {
            case Mode::Move:
                if (mSelectedDrawable != nullptr)
                {
                    if (mSelectedDrawable->IsMovable())
                    {
                        mSelectedDrawable->Move(delta);
                    }
                    else
                    {
                        mSelectedActor->SetPosition(mSelectedActor->GetPosition() + delta);
                    }
                    GetPicture()->UpdateObservers();
                }
            break;

            case Mode::Rotate:
                if (mSelectedDrawable != nullptr)
                {
                    mSelectedDrawable->SetRotation(mSelectedDrawable->GetRotation() + delta.y * RotationScaling);
                    GetPicture()->UpdateObservers();
                }
            break;

            default:
                break;
        }

    }
    else
    {
        mSelectedDrawable = nullptr;
        mSelectedActor = nullptr;
    }
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewEdit::UpdateObserver()
{
    Refresh();
}

/**
 * Sets KeyFrame when clicked
 * @param event Event
 */
void ViewEdit::SetKeyFrame(wxCommandEvent &event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
 * Deletes KeyFrame when clicked
 * @param event Event
 */
void ViewEdit::DeleteKeyFrame(wxCommandEvent &event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->DeleteKeyframe();
        picture->SetAnimationTime(picture->GetTimeline()->GetCurrentTime());
    }

}
