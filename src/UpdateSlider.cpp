#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* musicSliderArg, wxMediaCtrl* mediaPlayerArg) : wxTimer()
{
  setMusicSlider(musicSliderArg);
  setMediaPlayer(mediaPlayerArg);
  // Updates every second
  Start(1000);
}

void UpdateSlider::Notify()
{
  // Setting musicSlider range
  wxLongLong songLength = mediaPlayer->Length();
  int songLengthSeconds = (int) (songLength / 1000).GetValue();
  musicSlider->SetRange(0, songLengthSeconds);

  // Updating musicSlider position
  wxLongLong songAt = mediaPlayer->Tell();
  int songAtSeconds = (int) (songAt / 1000).GetValue();
  musicSlider->SetValue(songAtSeconds);
}

void UpdateSlider::setMusicSlider(wxSlider* musicSliderArg) { musicSlider = musicSliderArg; }
void UpdateSlider::setMediaPlayer(wxMediaCtrl* mediaPlayerArg) { mediaPlayer = mediaPlayerArg; }

