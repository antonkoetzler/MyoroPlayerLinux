// wxTimer derivation for controlling sliders and other music controls
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>
#include "SongList.h"
// rand()
#include <stdlib.h>

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*, SongList*);

  void Notify() wxOVERRIDE;

  // Setters
  void setMusicSlider(wxSlider*);
  void setMediaPlayer(wxMediaCtrl*);
  void setSonglist(SongList*);
  void setSongCache(wxVector<wxString>);
  void setShuffleToggle(int);

 private:
  wxSlider* musicSlider;
  wxMediaCtrl* mediaPlayer;
  SongList* songlist;
  wxVector<wxString> songCache;
  int shuffleToggle = 0;
};

