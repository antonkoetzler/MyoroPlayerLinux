#include "Controls.h"

BEGIN_EVENT_TABLE(Controls, wxPanel)
  EVT_MEDIA_LOADED(MEDIA, Controls::playSong)
  EVT_BUTTON(SHUFFLE, Controls::toggleShuffle)
  EVT_BUTTON(PLAY, Controls::togglePlay)
  EVT_BUTTON(PREV, Controls::previousSong)
  EVT_BUTTON(NEXT, Controls::nextSong)
END_EVENT_TABLE()

Controls::Controls(wxFrame* parent, SongList* songlistArg) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(1000, 90))
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
    wxSize(240, 40)
  );

  mediaPlayer = new wxMediaCtrl(this, MEDIA);
  updateSlider = new UpdateSlider(musicSlider, mediaPlayer);
  songlist = songlistArg;

  // Adding everything to the parent sizer
  sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(musicInformation, 0);
  sizer->AddStretchSpacer();
  sizer->Add(musicControl, 0);
  sizer->AddStretchSpacer();
  sizer->Add(volumeSlider, 0, wxALIGN_CENTRE_VERTICAL);
  SetSizer(sizer);
}

void Controls::setSongList(SongList* songlistArg) { songlist = songlistArg; }

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
    SHUFFLE,
    "%",
    wxDefaultPosition,
    wxSize(50, 40)
  );
  previous = new wxButton(
    this,
    PREV,
    "<<",
    wxDefaultPosition,
    wxSize(50, 40)
  );
  play = new wxButton(
    this,
    PLAY,
    ">",
    wxDefaultPosition,
    wxSize(50, 40)
  );
  next = new wxButton(
    this,
    NEXT,
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
  wxBitmap bitmap; bitmap.LoadFile("./img/noAlbumCover.png", wxBITMAP_TYPE_PNG);
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
    "Song Name",
    wxDefaultPosition,
    wxSize(150, 20),
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

void Controls::loadMediaPlayer(wxString songDirectory)
{
  if (!mediaPlayer->Load(songDirectory)) exit(1);
}

void Controls::playSong(wxMediaEvent& evt)
{
  mediaPlayer->Play();

  // Setting Controls::textInformation
  wxString songName = songlist->GetString(songlist->GetSelection());
  textInformation->SetLabel(songName);

  // Getting album name and icon
  wxString songDirectory = songlist->getPlaylistDirectory() + songName;

  static const char *IdPicture = "APIC";
  TagLib::MPEG::File mpegFile(songDirectory);
  TagLib::ID3v2::Tag *id3v2tag = mpegFile.ID3v2Tag();
  TagLib::ID3v2::FrameList Frame;
  TagLib::ID3v2::AttachedPictureFrame *PicFrame;
  void *RetImage = NULL, *SrcImage;
  unsigned long Size;
  FILE *jpegFile;
  jpegFile = fopen("FromId3.jpg", "wb");
  if ( id3v2tag )
  {
    // picture frame
    Frame = id3v2tag->frameListMap()[IdPicture] ;
    if (!Frame.isEmpty() )
    {
      for(TagLib::ID3v2::FrameList::ConstIterator it = Frame.begin(); it != Frame.end(); ++it)
      {
        PicFrame = (TagLib::ID3v2::AttachedPictureFrame *)(*it) ;
        //  if ( PicFrame->type() ==
        //TagLib::ID3v2::AttachedPictureFrame::FrontCover)
        {
          // extract image (in it’s compressed form)
          Size = PicFrame->picture().size() ;
          SrcImage = malloc ( Size ) ;
          if ( SrcImage )
          {
            memcpy ( SrcImage, PicFrame->picture().data(), Size ) ;
            fwrite(SrcImage,Size,1, jpegFile);
            fclose(jpegFile);
            free( SrcImage ) ;
          }
        }
      }
    }
  }

  wxBitmap bitmap; wxImage image; wxLogNull avoidErrors;
  bitmap.LoadFile("./FromId3.jpg", wxBITMAP_TYPE_JPEG);

  // Reloading Controls::albumCover
  delete albumCover;
  if (bitmap.IsOk())
  {
    image = bitmap.ConvertToImage();
    image.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);

    wxBitmap scaledBitmap(image, -1);
    albumCover = new wxStaticBitmap(this, wxID_ANY, scaledBitmap);
  }
  else
  {
    bitmap.LoadFile("./img/noAlbumCover.png", wxBITMAP_TYPE_PNG);
    image = bitmap.ConvertToImage();
    image.Rescale(80, 80, wxIMAGE_QUALITY_HIGH);

    wxBitmap scaledBitmap(image, -1);
    albumCover = new wxStaticBitmap(this, wxID_ANY, scaledBitmap);
  }

  // Must remove all of musicInformation's objects without deleting
  musicInformation->Clear(false);
  musicInformation->Add(albumCover, 0, wxALL, 5);
  musicInformation->Add(textInformation, 0, wxALIGN_CENTRE_VERTICAL);
  musicInformation->Layout();

  // Adding song to Controls::songCache
  songCache.push_back(songDirectory);
}

void Controls::toggleShuffle(wxCommandEvent& evt)
{
  switch (shuffleToggle)
  {
    case 0:
      shuffleToggle = 1;
      break;
    case 1:
      shuffleToggle = 0;
      break;
  }
}

void Controls::togglePlay(wxCommandEvent& evt)
{
  wxMediaState state = mediaPlayer->GetState();

  switch (state)
  {
    case wxMEDIASTATE_PLAYING:
      mediaPlayer->Pause();
      break;
    case wxMEDIASTATE_PAUSED:
      mediaPlayer->Play();
      break;
  }
}

void Controls::previousSong(wxCommandEvent& evt)
{
  // Since the current song is in the songCache, we need 2 in the vector
  if (songCache.size() > 1)
  {
    songCache.pop_back();
    wxString newSongDirectory = songCache[songCache.size() - 1]; // The previous song's directory
    wxString newSongName = wxEmptyString;                        // The previous song's name

    // Changing the highlighted song on songlist to new song
    for (int i = (newSongDirectory.length() - 1); i >= 0; i--)
    {
      if (newSongDirectory[i] == '/')
      {
        newSongName = newSongDirectory.substr(i + 1);
        break;
      }
    }

    songlist->SetSelection(songlist->FindString(newSongName));
    loadMediaPlayer(newSongDirectory);
  }
}

void Controls::nextSong(wxCommandEvent& evt)
{
  std::cout << "Hello game" << std::endl;
}

