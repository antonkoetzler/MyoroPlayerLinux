#pragma once

#include <wx/wx.h>

enum { TOGGLE_CONTROLS };

class MenuBar : public wxMenuBar
{
 public:
  MenuBar();

 private:
  wxMenu* file;
    wxMenuItem* fileExit;
  wxMenu* view;
    wxMenuItem* viewToggleControls;
};

