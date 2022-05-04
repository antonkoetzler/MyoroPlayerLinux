// wxTimer derivation for controlling sliders and other music controls
#pragma once

#include <wx/wx.h>
#include <wx/mediactrl.h>

class UpdateSlider : public wxTimer
{
 public:
  UpdateSlider(wxSlider*, wxMediaCtrl*);

  void Notify() wxOVERRIDE;

  // Setters
  void setMusicSlider(wxSlider*);
  void setMediaPlayer(wxMediaCtrl*);

 private:
  wxSlider* musicSlider;
  wxMediaCtrl* mediaPlayer;
};

