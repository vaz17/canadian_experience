/**
 * @file TimelineDlg.cpp
 * @author matthew vazquez
 */

#include "pch.h"
#include "TimelineDlg.h"

#include <wx/xrc/xmlres.h>
#include <wx/valnum.h>

#include "Timeline.h"

/**
 * Constructor
 * @param parent The parent window we will center in
 * @param timeline Pointer to the timeline we are editing
 */
TimelineDlg::TimelineDlg(wxWindow* parent, Timeline* timeline) : mTimeline(timeline)
{
 wxXmlResource::Get()->LoadDialog(this, parent, L"TimelineDlg");
 Bind(wxEVT_BUTTON, &TimelineDlg::OnOK, this, wxID_OK);

 mNumberOfFrames = timeline->GetNumFrames();
 auto numFramesCtrl = XRCCTRL(*this, "TimelineDlgNumFrames", wxTextCtrl);
 wxIntegerValidator<int> numFramesValidator(&mNumberOfFrames);
 numFramesValidator.SetRange(1, 10000);
 numFramesCtrl->SetValidator(numFramesValidator);

 mFrameRate  = timeline->GetFrameRate();
 auto frameRateCtrl = XRCCTRL(*this, "TimelineDlgFrameRate", wxTextCtrl);
 wxIntegerValidator<int> frameRateValidator(&mFrameRate);
 frameRateValidator.SetRange(1, 60);
 frameRateCtrl->SetValidator(frameRateValidator);


}

/**
 * Handle an OK button press
 * @param event Button event
 */
void TimelineDlg::OnOK(wxCommandEvent& event)
{
 if ( Validate() && TransferDataFromWindow() )
 {
  // Success! Set values in the class
  mTimeline->SetNumFrames(mNumberOfFrames);
  mTimeline->SetFrameRate(mFrameRate);

  EndModal(wxID_OK);
 }
}