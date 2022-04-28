// Bottom bar for music controls and information
#pragma once

#include <wx/wx.h>

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);

 private:
 // Parent sizer
 wxBoxSizer* sizer;
    // Play, pause, next, previous, shuffle
    wxBoxSizer* musicControl;
      wxSlider* musicSlider;
      wxBoxSizer* buttonsSizer;
        wxButton* shuffle;
        wxButton* previous;
        wxButton* play;
        wxButton* next;
};

