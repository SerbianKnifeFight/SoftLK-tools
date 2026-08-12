# SLK_img2pixel, june's fork

This is a fork of Captain4LK's SLK_img2pixel (https://github.com/Captain4LK/SoftLK-tools), a tool for turning images into pixel art. Everything the original tool does, it still does. This fork only adds on top of it. For full usage instructions, including everything below, see MANUAL.md.

## What's new here

- **8 more dither algorithms**: Bayer 3x3 and 5x5, Stucki, Burkes, Sierra, Sierra Two-Row, Sierra Lite, and a PicoCAD-style checkerboard dither, alongside the original Bayer, Cluster, Floyd-Steinberg, and Median-Cut modes.
- **Animated GIF import and export**, in both the GUI and the command-line tool.
- **A customizable UI theme** (the Theme tab): edit the app's own colors with hex codes. Your choices persist across restarts.
- **Lua scripting**, in both the GUI (Tools > Run script...) and the command line (--script file.lua). You can automate batch conversions, sweep settings, render every dither mode for comparison, and so on. Full reference in LUA_SCRIPTING.md.

Nothing existing was removed or changed in behavior. Default settings, existing presets, and existing palettes all still work exactly like before.

## Building from source

Same dependencies as upstream (just SDL2, Lua is vendored directly into external/lua/, so there's no separate install needed).

```sh
cd SLK_img2pixel
make          # or: sh linux.sh | make -f -   (regenerates the makefile first)
```

Binaries land in ../bin/. mac.sh and win_cross.sh work the same way for macOS and Windows cross-compilation. See upstream's README.md for the general build-script pattern; this fork's scripts follow the same shape, just with the new source files added in.

### A note on win_cross.sh

This script hardcodes the original author's own toolchain path (/mnt/sdb1/apps/llvm-mingw-...). That's a pre-existing quirk from upstream, not something this fork introduced. You'll need to point CC and CXX at your own mingw-w64 toolchain if you use it. If you just want a Windows build without fighting that script, a plain mingw-w64 cross-compile works fine too. See the "Building on Windows" section in MANUAL.md.

## What wasn't touched

This repository also contains two other, unrelated programs: SLK_make (an experimental build system) and pixtexed (an in-progress pixel art and texture editor, not yet listed in the top-level README). Neither was touched by this fork. They build (or don't) exactly as they did before. If you're looking for either of those, that's a separate project from anything covered here.

## License

Same as upstream: everything except external/ (third-party code) is public domain (CC0), see COPYING. The newly-vendored Lua interpreter in external/lua/ is MIT-licensed, same as it is upstream at lua.org.
