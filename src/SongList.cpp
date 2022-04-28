#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, SONGLIST, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_NEEDED_SB | wxLB_SORT)
{
  directory = new wxDir("./songs/");

  if (!directory->IsOpened()) exit(1);

  wxString fileName;
  wxString fileExtension;
  bool cont = directory->GetFirst(&fileName, wxEmptyString, wxDIR_FILES);
  while (cont)
  {
    // Grabbing the file extension (if there is one)
    for (int i = (fileName.length() - 1); i >= 0; i--)
    {
      if (fileName[i] == '.')
      {
        fileExtension = fileName.substr(i + 1);
        fileExtension.MakeUpper();
        break;
      }
      if (i == 0)
      {
        fileExtension = wxEmptyString;
        break;
      }
    }

    if (fileExtension != wxEmptyString && fileExtension == "MP3") Append(fileName);

    cont = directory->GetNext(&fileName);
  }

  delete directory; directory = nullptr;
}

