#include "SongList.h"

SongList::SongList(wxFrame* parent) : wxListBox(parent, SONGLIST, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_NEEDED_SB | wxLB_SORT)
{
  Append("Hello, World!");
}

