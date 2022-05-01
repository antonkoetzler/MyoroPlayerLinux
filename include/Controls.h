// Bottom bar for music controls and information
#pragma once

#include <wx/wx.h>

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*);
 
  // Helper functions
  void initMusicControl();
  void initMusicInformation();

 private:
 // Parent sizer
 wxBoxSizer* sizer;
   // Album cover, song name, song album
   wxBoxSizer* musicInformation;
     wxStaticBitmap* albumCover;    // Album cover
     wxStaticText* textInformation; // Song name, song album
   // Play, pause, next, previous, shuffle
   wxBoxSizer* musicControl;
     wxSlider* musicSlider;
     wxBoxSizer* buttonsSizer;
       wxButton* shuffle;
       wxButton* previous;
       wxButton* play;
       wxButton* next;
   // Volume slider
   wxSlider* volumeSlider;
};

