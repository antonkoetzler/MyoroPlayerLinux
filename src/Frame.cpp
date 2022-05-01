#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(TOGGLE_CONTROLS, Frame::toggleControls)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayerLinux", wxDefaultPosition, wxSize(1000, 800))
{
  // Need to init JPEG image handler
  wxImage::AddHandler(new wxJPEGHandler);

  songlist = new SongList(this);
  controls = new Controls(this); controls->Show(false);
  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(songlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);
  SetSizer(sizer);

  menubar = new MenuBar();
  SetMenuBar(menubar);
  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::toggleControls(wxCommandEvent& evt)
{
  if (!controls->IsShown()) controls->Show(true);
  else                      controls->Show(false);
  sizer->Layout();
}

