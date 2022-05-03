#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "SongList.h"
#include "Controls.h"

enum
{
  CHANGE_DIRECTORY_INPUT,
  CHANGE_DIRECTORY_BUTTON
};

class Frame : public wxFrame
{
 public:
  Frame();
  ~Frame();

  void showChangeDirectory(wxCommandEvent&);
    void changeDirectory(wxCommandEvent&);
  void exit(wxCommandEvent&);
  void toggleControls(wxCommandEvent&);

 private:
  DECLARE_EVENT_TABLE();

  MenuBar* menubar;
  wxBoxSizer* sizer;
    SongList* songlist;
    Controls* controls;

  // For YT2MP3 and changing directory
  wxFrame* popupWindow = nullptr;
  wxTextCtrl* popupWindowInput = nullptr;
  wxButton* popupWindowButton = nullptr;
  wxSizer* popupWindowSizer = nullptr;
};

