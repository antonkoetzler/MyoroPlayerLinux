#include "MenuBar.h"

MenuBar::MenuBar() : wxMenuBar()
{
  fileExit = new wxMenuItem(nullptr, wxID_EXIT, "Exit\tCtrl+Q");
  file = new wxMenu();
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

