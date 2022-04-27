#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"
#include "Controls.h"

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  void exit(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;
  wxBoxSizer* sizer;
    SongList* songlist;
    Controls* controls = nullptr;
};

