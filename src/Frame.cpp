#include "Frame.h"

BEGIN_EVENT_TABLE(Frame, wxFrame)
  // Menubar
  EVT_MENU(YT2MP3, Frame::showYouTubeToMP3)
  EVT_MENU(CHANGE_DIRECTORY, Frame::showChangeDirectory)
  EVT_MENU(wxID_EXIT, Frame::exit)
  EVT_MENU(REFRESH, Frame::refreshPlaylist)
  EVT_MENU(TOGGLE_CONTROLS, Frame::toggleControls)
  // Right click menu
  EVT_MENU(QUEUE, Frame::queueSong)

  // Popup window (change playlist & youtube to mp3 popup windows)
  EVT_TEXT_ENTER(CHANGE_DIRECTORY_INPUT, Frame::changeDirectory)
  EVT_BUTTON(CHANGE_DIRECTORY_BUTTON, Frame::changeDirectory)
  EVT_TEXT_ENTER(YT2MP3_INPUT, Frame::YouTubeToMP3)
  EVT_BUTTON(YT2MP3_BUTTON, Frame::YouTubeToMP3)

  // SongList*
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

  // Frame::playlistMenu is the right click menu to, i.e., queue songs
  // We bind this only to playlist as we want the right click to work only on playlist
  songlist->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(Frame::playlistMenu), nullptr, this);
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
    songlist->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(Frame::playlistMenu), nullptr, this);


    // Updating pointers to songlist
    controls->setSongList(songlist);
    controls->setUpdateSliderSonglist(songlist);

    sizer->Add(songlist, 1, wxEXPAND);
    sizer->Add(controls, 0, wxEXPAND);
    sizer->Layout();

    popupWindow->Close(); popupWindow->Destroy();
    delete popupWindow; popupWindow = nullptr;
  }
}

void Frame::showYouTubeToMP3(wxCommandEvent& evt)
{
  popupWindow = new wxFrame(
    this,
    wxID_ANY,
    "YouTube To MP3",
    wxDefaultPosition,
    wxSize(300, 90)
  );

  popupWindowInput = new wxTextCtrl(
    popupWindow,
    YT2MP3_INPUT,
    wxEmptyString,
    wxDefaultPosition,
    wxDefaultSize,
    wxTE_CENTRE | wxTE_PROCESS_ENTER
  );

  popupWindowButton = new wxButton(
    popupWindow,
    YT2MP3_BUTTON,
    "Convert To MP3",
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

void Frame::YouTubeToMP3(wxCommandEvent& evt)
{
  if (popupWindowInput->GetLineText(0) == wxEmptyString)
  {
    popupWindow->Close(); popupWindow->Destroy();
    delete popupWindow; popupWindow = nullptr;
    return;
  }

  wxString command = "youtube-dl --extract-audio --audio-format mp3 -o \"" + songlist->getPlaylistDirectory() + "%(title)s-%(id)s.mp3\" " + popupWindowInput->GetLineText(0);
  wxExecute(command);

  wxMessageDialog* message = new wxMessageDialog(
    nullptr,
    "Refresh your playlist once the download has completed.",
    wxEmptyString,
    wxOK | wxCENTRE
  );
  message->ShowModal();

  popupWindow->Close(); popupWindow->Destroy();
  delete popupWindow; popupWindow = nullptr;
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

void Frame::playlistMenu(wxMouseEvent& evt)
{
  wxClientDC dc(this);
  songlist->SetSelection(songlist->HitTest(evt.GetLogicalPosition(dc)));

  wxMenuItem* popupQueue = new wxMenuItem(nullptr, QUEUE, "Queue");
  wxMenu* popup = new wxMenu();
  popup->Append(popupQueue);

  PopupMenu(popup, wxDefaultPosition);
}

void Frame::queueSong(wxCommandEvent& evt)
{
  wxString songDirectory = songlist->getPlaylistDirectory() + songlist->GetString(songlist->GetSelection());
  songlist->addToQueue(songDirectory);
}

void Frame::refreshPlaylist(wxCommandEvent& evt)
{
  // Clearing sizer objects without deleting objects
  sizer->Clear(false);

  // Creating a new SongList
  wxString playlistDirectory = songlist->getPlaylistDirectory();
  delete songlist;
  songlist = new SongList(this, playlistDirectory);
  songlist->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(Frame::playlistMenu), nullptr, this);


  // Updating pointers to songlist
  controls->setSongList(songlist);
  controls->setUpdateSliderSonglist(songlist);

  // Adding objects back to sizer
  sizer->Add(songlist, 1, wxEXPAND);
  sizer->Add(controls, 0, wxEXPAND);
  sizer->Layout();
}

