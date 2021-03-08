# Allans FrameworK

![Build Windows](https://github.com/AdsGames/AfkLib/workflows/Build%20Windows/badge.svg)
![Build Linux](https://github.com/AdsGames/AfkLib/workflows/Build%20Linux/badge.svg)
![Build Mac OS](https://github.com/AdsGames/AfkLib/workflows/Build%20Mac%20OS/badge.svg)
![Build Web](https://github.com/AdsGames/AfkLib/workflows/Build%20Web/badge.svg)

Game framework

## Documentation

[Doxygen Generated Documentation](https://adsgames.github.io/AfkLib/)

## Setup

### Windows (MSYS2)

#### Install Libraries

```bash
pacman --noconfirm -S mingw-w64-i686-gcc-libs mingw-w64-i686-dumb mingw-w64-i686-flac mingw-w64-i686-opusfile mingw-w64-i686-freetype mingw-w64-i686-libjpeg-turbo mingw-w64-i686-libpng mingw-w64-i686-libvorbis mingw-w64-i686-libwebp mingw-w64-i686-openal mingw-w64-i686-physfs mingw-w64-i686-allegro
```

#### Build

```bash
cmake -G "MSYS Makefiles" .
```

```bash
make
```

### Mac OS

#### Install Libraries

```bash
brew install allegro
```

#### Build

```bash
cmake -G "Unix Makefiles" .
```

```bash
make
```

### Linux

#### Install Libraries

```bash
sudo apt install liballegro5-dev liballegro-acodec5-dev liballegro-audio5-dev liballegro-image5-dev liballegro-dialog5-dev liballegro-ttf5-dev
```

#### Build

```bash
cmake -G "Unix Makefiles" .
```

```bash
make
```
