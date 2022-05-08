#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileYouTubeToMP3 = new wxMenuItem(
    nullptr,
    YT2MP3,
    "YouTube To MP3\tCtrl+Y"
  );
  fileChangeDirectory = new wxMenuItem(
    nullptr,
    CHANGE_DIRECTORY,
    "Change Playlist Directory\tCtrl+O"
  );
  fileExit = new wxMenuItem(nullptr, wxID_EXIT, "Exit\tCtrl+Q");
  file = new wxMenu();
  file->Append(fileYouTubeToMP3);
  file->Append(fileChangeDirectory);
  file->Append(fileExit);
  Append(file, "File");

  viewRefreshPlaylist = new wxMenuItem(
    nullptr,
    REFRESH,
    "Refresh playlist\tCtrl+R"
  );
  viewToggleControls = new wxMenuItem(
    nullptr,
    TOGGLE_CONTROLS,
    "Show/Hide Controls"
  );
  view = new wxMenu();
  view->Append(viewRefreshPlaylist);
  view->Append(viewToggleControls);
  Append(view, "View");
}

