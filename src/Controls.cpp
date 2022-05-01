#include "Controls.h"

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
{
  initMusicInformation();
  initMusicControl();

  volumeSlider = new wxSlider(
    this,
    wxID_ANY,
    50,
    0,
    100,
    wxDefaultPosition,
    wxSize(150, 40)
  );

  // Adding everything to the parent sizer
  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(musicInformation, 0);
  sizer->AddStretchSpacer();
  sizer->Add(musicControl, 0);
  sizer->AddStretchSpacer();
  sizer->Add(volumeSlider, 0, wxALIGN_CENTRE_VERTICAL);
  SetSizer(sizer);
}

void Controls::initMusicControl()
{
  musicSlider = new wxSlider(
    this,
    wxID_ANY,
    50,
    0,
    100,
    wxDefaultPosition,
    wxSize(250, 40)
  );

  shuffle = new wxButton(
    this,
    wxID_ANY,
    "%",
    wxDefaultPosition,
    wxSize(50, 40)
  );
  previous = new wxButton(
    this,
    wxID_ANY,
    "<<",
    wxDefaultPosition,
    wxSize(50, 40)
  );
  play = new wxButton(
    this,
    wxID_ANY,
    ">",
    wxDefaultPosition,
    wxSize(50, 40)
  );
  next = new wxButton(
    this,
    wxID_ANY,
    ">>",
    wxDefaultPosition,
    wxSize(50, 40)
  );

  buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
  buttonsSizer->Add(shuffle, 0, wxRIGHT, 10);
  buttonsSizer->Add(previous, 0, wxRIGHT, 10);
  buttonsSizer->Add(play, 0, wxRIGHT, 10);
  buttonsSizer->Add(next, 0);

  musicControl = new wxBoxSizer(wxVERTICAL);
  musicControl->Add(musicSlider, 0);
  musicControl->Add(buttonsSizer, 0, wxALIGN_CENTRE_HORIZONTAL);
}

void Controls::initMusicInformation()
{
  wxBitmap bitmap; bitmap.LoadFile("./img/FromId3.jpg", wxBITMAP_TYPE_JPEG);
  if (!bitmap.IsOk()) { exit(1); }

  // Converting wxBitmap to wxImage to use wxImage::Rescale
  wxImage image = bitmap.ConvertToImage();
  image.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);
  
  // Setting album cover
  wxBitmap scaledBitmap(image, -1);
  albumCover = new wxStaticBitmap(this, wxID_ANY, scaledBitmap);

  // Setting the song name and album
  textInformation = new wxStaticText(
    this,
    wxID_ANY,
    "Song Name\nSong Album",
    wxDefaultPosition,
    wxSize(100, 32),
    wxST_NO_AUTORESIZE | wxST_ELLIPSIZE_END
  );
  textInformation->SetFont(wxFont(
    12,
    wxFONTFAMILY_DEFAULT,
    wxFONTSTYLE_NORMAL,
    wxFONTWEIGHT_NORMAL
  ));

  musicInformation = new wxBoxSizer(wxHORIZONTAL);
  musicInformation->Add(albumCover, 0, wxALL, 5);
  musicInformation->Add(textInformation, 0, wxALIGN_CENTRE_VERTICAL);
}

