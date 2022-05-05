#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU(CHANGE_DIRECTORY, Frame::showChangeDirectory)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(TOGGLE_CONTROLS, Frame::toggleControls)

  EVT_TEXT_ENTER(CHANGE_DIRECTORY_INPUT, Frame::changeDirectory)
  EVT_BUTTON(CHANGE_DIRECTORY_BUTTON, Frame::changeDirectory)

  EVT_LISTBOX_DCLICK(SONGLIST, Frame::loadSong)
END_EVENT_TABLE()

Frame::Frame() : wxFrame(nullptr, wxID_ANY, "MyoroPlayerLinux", wxDefaultPosition, wxSize(1000, 800))
{
  // Need to init JPEG & PNG image handler
  wxImage::AddHandler(new wxJPEGHandler);
  wxImage::AddHandler(new wxPNGHandler);

  songlist = new SongList(this);
  controls = new Controls(this, songlist); controls->Show(false);
  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(songlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);
  SetSizer(sizer);

  menubar = new MenuBar();
  SetMenuBar(menubar);
  Centre();
}

Frame::~Frame() { Destroy(); }

void Frame::showChangeDirectory(wxCommandEvent& evt)
{
  popupWindow = new wxFrame(
    this,
    wxID_ANY,
    "Change Directory",
    wxDefaultPosition,
    wxSize(300, 90)
  );

  popupWindowInput = new wxTextCtrl(
    popupWindow,
    CHANGE_DIRECTORY_INPUT,
    wxEmptyString,
    wxDefaultPosition,
    wxDefaultSize,
    wxTE_CENTRE | wxTE_PROCESS_ENTER
  );

  popupWindowButton = new wxButton(
    popupWindow,
    CHANGE_DIRECTORY_BUTTON,
    "Change Directory",
    wxDefaultPosition,
    wxSize(300, 25),
    wxBORDER_NONE
  );

  popupWindowSizer = new wxBoxSizer(wxVERTICAL);
  popupWindowSizer->Add(popupWindowInput, 1, wxEXPAND);
  popupWindowSizer->Add(popupWindowButton, 0, wxEXPAND);

  popupWindow->SetSizerAndFit(popupWindowSizer);
  popupWindow->Show(true);
  popupWindow->Centre();
}

void Frame::changeDirectory(wxCommandEvent& evt)
{
  wxString directory = popupWindowInput->GetLineText(0);
  if (directory != wxEmptyString)
  {
    // Clearing sizer's items without deleting them
    sizer->Clear(false);

    // Creating a new SongList
    delete songlist;
    songlist = new SongList(this, directory);

    // Updating controls' pointer to songlist
    controls->setSongList(songlist);

    sizer->Add(songlist, 1, wxEXPAND);
    sizer->Add(controls, 0, wxEXPAND);
    sizer->Layout();

    popupWindow->Close(); popupWindow->Destroy();
    delete popupWindow; popupWindow = nullptr;
  }
}

void Frame::exit(wxCommandEvent& evt) { Close(); }

void Frame::toggleControls(wxCommandEvent& evt)
{
  if (!controls->IsShown()) controls->Show(true);
  else                      controls->Show(false);
  sizer->Layout();
}

void Frame::loadSong(wxCommandEvent& evt)
{
  if (!controls->IsShown())
  {
    controls->Show(true);
    sizer->Layout();
  }

  wxString songDirectory = songlist->getPlaylistDirectory() + evt.GetString();
  controls->loadMediaPlayer(songDirectory);
}

