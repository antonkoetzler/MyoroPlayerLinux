// Bottom bar for music controls and information
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "UpdateSlider.h"
#include "SongList.h"
// For finding album name and icon
#include <taglib/id3v2tag.h>
#include <taglib/mpegfile.h>
#include <taglib/id3v2frame.h>
#include <taglib/id3v2header.h>
#include <taglib/attachedpictureframe.h>
#include <cstdio>
#include <string.h>
// rand()
#include <stdlib.h>

enum
{
  MEDIA,
  SHUFFLE,
  PREV,
  PLAY,
  NEXT
};

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
  void toggleShuffle(wxCommandEvent&);
  void togglePlay(wxCommandEvent&);
  void previousSong(wxCommandEvent&);
  void nextSong(wxCommandEvent&);

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
  wxVector<wxString> songCache;

  int shuffleToggle = 0;
};

