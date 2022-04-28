#include "Controls.h"

Controls::Controls(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
{
  // Init music/song slider
  musicSlider = new wxSlider(
    this,
    wxID_ANY,
    50,
    0,
    100,
    wxDefaultPosition,
    wxSize(250, 40)
  );

  // Init buttons
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

  // Placing buttons in buttonsSizer
  buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
  buttonsSizer->Add(shuffle, 0, wxRIGHT, 10);
  buttonsSizer->Add(previous, 0, wxRIGHT, 10);
  buttonsSizer->Add(play, 0, wxRIGHT, 10);
  buttonsSizer->Add(next, 0);

  // Adding music slider & buttons to musicControl
  musicControl = new wxBoxSizer(wxVERTICAL);
  musicControl->Add(musicSlider, 0);
  musicControl->Add(buttonsSizer, 0, wxALIGN_CENTRE_HORIZONTAL);

  // Adding everything to the parent sizer
  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->AddStretchSpacer();
  sizer->Add(musicControl, 0);
  sizer->AddStretchSpacer();
  SetSizer(sizer);
}

