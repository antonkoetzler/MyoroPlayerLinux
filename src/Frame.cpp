#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayerLinux")
{
  songlist = new SongList(this);
  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(songlist, 1, wxEXPAND);
  SetSizer(sizer);

  menubar = new MenuBar();
  SetMenuBar(menubar);
  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

