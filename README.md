# Allans FrameworK

![Build Windows](https://github.com/AdsGames/AfkLib/workflows/Build%20Windows/badge.svg)
![Build Linux](https://github.com/AdsGames/AfkLib/workflows/Build%20Linux/badge.svg)
![Build Mac OS](https://github.com/AdsGames/AfkLib/workflows/Build%20Mac%20OS/badge.svg)
![Build Web](https://github.com/AdsGames/AfkLib/workflows/Build%20Web/badge.svg)

Game framework

## Documentation

[Doxygen Generated Documentation](https://adsgames.github.io/AfkLib/)

## Examples (Web)

- [ex_collision](https://adsgames.github.io/AfkLib/examples/ex_collision.html)
- [ex_display](https://adsgames.github.io/AfkLib/examples/ex_display.html)
- [ex_fps](https://adsgames.github.io/AfkLib/examples/ex_fps.html)
- [ex_keyboard](https://adsgames.github.io/AfkLib/examples/ex_keyboard.html)
- [ex_message_box](https://adsgames.github.io/AfkLib/examples/ex_message_box.html)
- [ex_mouse](https://adsgames.github.io/AfkLib/examples/ex_mouse.html)
- [ex_particles](https://adsgames.github.io/AfkLib/examples/ex_particles.html)
- [ex_rotate](https://adsgames.github.io/AfkLib/examples/ex_rotate.html)
- [ex_sound](https://adsgames.github.io/AfkLib/examples/ex_sound.html)
- [ex_sprite](https://adsgames.github.io/AfkLib/examples/ex_sprite.html)
- [ex_ui](https://adsgames.github.io/AfkLib/examples/ex_ui.html)

## Setup

### Windows (MSYS2)

```bash
pacman -S mingw-w64-i686-gcc-libs mingw-w64-i686-SDL2 mingw-w64-i686-SDL2_mixer mingw-w64-i686-SDL2_image mingw-w64-i686-SDL2_ttf mingw-w64-i686-SDL2_gfx
```

### Mac OS

```bash
brew install sdl2 sdl2_image sdl2_gfx sdl2_ttf sdl2_mixer
```

### Linux

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-gfx-dev
```

### Build

```bash
cmake .
```

```bash
make
```

### Build Emscripten

```bash
emcmake cmake .
```

```bash
make
```

### Install Library (works for emscripten)

```bash
make install
```
