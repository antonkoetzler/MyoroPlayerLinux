#include "UpdateSlider.h"

UpdateSlider::UpdateSlider(wxSlider* musicSliderArg, wxMediaCtrl* mediaPlayerArg, SongList* songlistArg) : wxTimer()
{
  setMusicSlider(musicSliderArg);
  setMediaPlayer(mediaPlayerArg);
  setSonglist(songlistArg);
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

  // End of song (autoplay) condition
  if (mediaPlayer->GetState() == wxMEDIASTATE_STOPPED)
  {
    // Result variable, index of songlist we'll be playing
    int nextSongIndex = 0;

    // Getting the name from current song playingA
    wxString songName = wxEmptyString;
    for (int i = (songCache[songCache.size() - 1].length() - 1); i >= 0; i--)
    {
      if (songCache[songCache.size() - 1][i] == '/')
      {
        songName = songCache[songCache.size() - 1].substr(i + 1);
        break;
      }
    }

    // No queued songs available
    if (songlist->getQueue().empty())
    {
      // No shuffle, if current song's index is songlist->GetCount(), nextSongIndex stays 0
      if (shuffleToggle == 0)
      {
        if ((songlist->GetCount() - 1) != songlist->FindString(songName))
          nextSongIndex = songlist->FindString(songName) + 1;
      }
      // Shuffle
      else
      {
        int currentSongIndex = songlist->FindString(songName);

        // Generate random index that isn't equal to currentSongIndex
        while (true)
        {
          nextSongIndex = rand() % songlist->GetCount();
          if (nextSongIndex != currentSongIndex) break;
        }
      }
    }
    // Queued songs available
    else
    {
      wxString nextSongDirectory = songlist->getQueue()[0];
      wxString nextSongName;
      songlist->removeFromQueue();

      // Removing directory from nextSongDirectory
      for (int i = (nextSongDirectory.length() - 1); i >= 0; i--)
      {
        if (nextSongDirectory[i] == '/')
        {
          nextSongName = nextSongDirectory.substr(i + 1);
          break;
        }
      }

      nextSongIndex = songlist->FindString(nextSongName);
    }

    // Loading and changing highlighted song on songlist
    wxString songDirectory = songlist->getPlaylistDirectory() + songlist->GetString(nextSongIndex);
    songlist->SetSelection(nextSongIndex);
    if (!mediaPlayer->Load(songDirectory)) exit(1);
  }
}

void UpdateSlider::setMusicSlider(wxSlider* musicSliderArg) { musicSlider = musicSliderArg; }
void UpdateSlider::setMediaPlayer(wxMediaCtrl* mediaPlayerArg) { mediaPlayer = mediaPlayerArg; }
void UpdateSlider::setSonglist(SongList* songlistArg) { songlist = songlistArg; }
void UpdateSlider::setSongCache(wxVector<wxString> songCacheArg)
{
  songCache.clear();
  for (size_t i = 0; i < songCacheArg.size(); i++) songCache.push_back(songCacheArg[i]);
}
void UpdateSlider::setShuffleToggle(int shuffleToggleArg) { shuffleToggle = shuffleToggleArg; }

