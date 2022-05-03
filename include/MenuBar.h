#pragma once

#include <wx/wx.h>

enum
{
  TOGGLE_CONTROLS,
  CHANGE_DIRECTORY
};

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileChangeDirectory;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* viewToggleControls;
};

