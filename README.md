# MyoroPlayerLinux
A clone of https://www.github.com/antonkoetzler/MyoroPlayer exclusive to Linux. MyoroPlayerLinux is a libre MP3 player with Youtube to MP3 functionality.

# Installing
## Installing Normally (Using Pre-Compiled Binaries)
1. Go to: https://github.com/antonkoetzler/MyoroPlayerLinux/releases/tag/1.0
2. Download MyoroPlayerLinux.zip
3. `unzip MyoroPlayerLinux.zip; cd MyoroPlayerLinux; sh install.sh`
4. Install dependancies: `sudo pacman -S youtube-dl gtk3 base-devel`
## Installing Through Source
- Prerequisites
  1. CMake
  2. C++ compiler (`build-essential`, `base-devel`, etc)
  3. Compiled wxWidgets source
    - Instructions: https://github.com/antonkoetzler/wxWidgets/blob/main/Installation/LinuxInstallation.pdf
  4. `youtube-dl`, `gtk3`
1. Download MyoroPlayerLinux's contents (GitHub "Download ZIP" option)
2. Extract MyoroPlayerLinux-main.zip
3. `cd MyoroPlayerLinux-main; sh build.sh`
5. Place binaries wherever
  - You'll need `./img/`, `./songs/`, and `MyoroPlayerLinux` (executable itself)

Inspired by Audacity
