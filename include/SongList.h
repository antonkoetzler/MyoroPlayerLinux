#pragma once

#include <wx/wx.h>
#include <wx/dir.h>

enum { SONGLIST };

class SongList : public wxListBox
{
 public:
  SongList(wxFrame*);
  SongList(wxFrame*, wxString);

  void appendSongs();
  wxVector<wxString> getQueue();
  void addToQueue(wxString);
  void removeFromQueue();
  wxString getPlaylistDirectory();

 private:
  wxDir* directory;
  wxString playlistDirectory = wxGetCwd() + "/songs/";
  wxVector<wxString> queue;
};

