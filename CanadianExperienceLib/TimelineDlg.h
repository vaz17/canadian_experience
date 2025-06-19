/**
 * @file TimelineDlg.h
 * @author matthew vazquez
 *
 *
 */
 
#ifndef TIMELINEDLG_H
#define TIMELINEDLG_H


class Timeline;

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
 /// Pointer to Timeline
 Timeline * mTimeline = nullptr;

 /// Number of frames in the animation
 int mNumberOfFrames;

 /// Frame rate of animation
 int mFrameRate;

public:
 TimelineDlg(wxWindow* parent, Timeline* timeline);
 void OnOK(wxCommandEvent& event);
};



#endif //TIMELINEDLG_H
