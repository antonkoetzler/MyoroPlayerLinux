// Bottom bar for music controls and information
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "UpdateSlider.h"
#include "SongList.h"

enum { MEDIA };

class Controls : public wxPanel
{
 public:
  Controls(wxFrame*, SongList*);
  
  // Getters and setters
  void setSongList(SongList*);
 
  // Helper functions
  void initMusicControl();
  void initMusicInformation();
  void loadMediaPlayer(wxString);

  // Event functions
  void playSong(wxMediaEvent&);

 private:
  DECLARE_EVENT_TABLE();

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

  wxMediaCtrl* mediaPlayer;
  UpdateSlider* updateSlider;
  SongList* songlist;
};

