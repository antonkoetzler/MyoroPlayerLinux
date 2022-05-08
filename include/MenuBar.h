#pragma once

#include <wx/wx.h>

enum
{
  TOGGLE_CONTROLS,
  CHANGE_DIRECTORY,
  REFRESH,
  YT2MP3
};

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileYouTubeToMP3;
    wxMenuItem* fileChangeDirectory;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* viewRefreshPlaylist;
    wxMenuItem* viewToggleControls;
};

