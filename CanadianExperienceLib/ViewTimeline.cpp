/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>

#include "ViewTimeline.h"

#include <sstream>

#include "Picture.h"
#include "TimelineDlg.h"

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";

using namespace std;

/**
 * Constructor
 * @param parent The main wxFrame object
 */
ViewTimeline::ViewTimeline(wxFrame* parent) :
    wxScrolled(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
             &ViewTimeline::OnEditTimelineProperties, this,
             XRCID("EditTimelineProperties"));


}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    mPointerImage = make_unique<wxImage>(mImagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);


    auto size = dc.GetSize();
    auto timeline = GetPicture()->GetTimeline();
    int numOfTicks = timeline->GetNumFrames();
    int frameRate = timeline->GetFrameRate();
    int TickBottom;
    int tickX = BorderLeft;

    SetVirtualSize(numOfTicks * TickSpacing + BorderLeft + BorderRight, size.y);
    SetScrollRate(1, 0);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));
    mPointerBitmap = graphics->CreateBitmap(*mPointerImage);

    wxPen pen(wxColour(*wxBLACK));
    graphics->SetPen(pen);

    wxFont font(wxSize(0, 16),
           wxFONTFAMILY_SWISS,
           wxFONTSTYLE_NORMAL,
           wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);



    for (int tickNum = 0; tickNum < numOfTicks; tickNum++)
    {
     bool onSecond = (tickNum % frameRate) == 0;
     if (onSecond)
     {
      TickBottom = TickTop + TickLong;
      // Convert the tick number to seconds in a string
      std::wstringstream str;
      str << tickNum / timeline->GetFrameRate();
      std::wstring wstr = str.str();

      double w, h;
      graphics->GetTextExtent(wstr, &w, &h);

      graphics->DrawText(wstr, tickX - w/2, TickTop + TickShort + h);
     } else
     {
      TickBottom = TickTop + TickShort;
     }
     graphics->StrokeLine(tickX, TickTop, tickX, TickBottom);

     if (tickNum == timeline->GetCurrentFrame())
     {
      graphics->DrawBitmap(mPointerBitmap,
      tickX - mPointerImage->GetWidth()/2, TickTop,
    mPointerImage->GetWidth(),
    mPointerImage->GetHeight());
     }



     tickX += TickSpacing;
    }

}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
 auto click = CalcUnscrolledPosition(event.GetPosition());

 int x = click.x;

 // Get the timeline
 Timeline *timeline = GetPicture()->GetTimeline();
 int pointerX = (int)(timeline->GetCurrentTime() *
         timeline->GetFrameRate() * TickSpacing + BorderLeft);

 mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
         x <= pointerX + mPointerImage->GetWidth() / 2;
}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
 if (mMovingPointer)
 {
  if (event.LeftIsDown())
  {
   auto click = CalcUnscrolledPosition(event.GetPosition());
   int x = click.x;

   // Get the timeline
   Timeline *timeline = GetPicture()->GetTimeline();
   double time = (x - BorderLeft) / (double)(TickSpacing * timeline->GetFrameRate());
   if (0 <= time && time < timeline->GetNumFrames() / timeline->GetFrameRate())
   {
    GetPicture()->SetAnimationTime(time);
   }
  } else
  {
   mMovingPointer = false;
  }
 }


}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{
 TimelineDlg dlg(this->GetParent(), GetPicture()->GetTimeline());
 if(dlg.ShowModal() == wxID_OK)
 {
  // The dialog box has changed the Timeline settings
  GetPicture()->UpdateObservers();

 }
}