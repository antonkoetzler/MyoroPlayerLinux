#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileChangeDirectory = new wxMenuItem(
    nullptr,
    CHANGE_DIRECTORY,
    "Change Playlist Directory\tCtrl+O"
  );
  fileExit = new wxMenuItem(nullptr, wxID_EXIT, "Exit\tCtrl+Q");
  file = new wxMenu();
  file->Append(fileChangeDirectory);
  file->Append(fileExit);
  Append(file, "File");

  viewToggleControls = new wxMenuItem(
    nullptr,
    TOGGLE_CONTROLS,
    "Show/Hide Controls"
  );
  view = new wxMenu();
  view->Append(viewToggleControls);
  Append(view, "View");
}

