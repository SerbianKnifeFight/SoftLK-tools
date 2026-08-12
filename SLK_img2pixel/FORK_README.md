# SLK_img2pixel — this fork

This is a fork of [Captain4LK's SLK_img2pixel](https://github.com/Captain4LK/SoftLK-tools),
a tool for turning images into pixel art. Everything the original tool
does, it still does, this fork only adds on top of it. For full usage
instructions (including everything below), see [MANUAL.md](MANUAL.md).

## What's new here

- **8 more dither algorithms**: Bayer 3x3 and 5x5, Stucki, Burkes, Sierra,
  Sierra Two-Row, Sierra Lite, and a PicoCAD-style checkerboard dither,
  alongside the original Bayer/Cluster/Floyd-Steinberg/Median-Cut modes.
- **Animated GIF import & export**, in both the GUI and the command-line
  tool.
- **A customizable UI theme** (Theme tab): edit the app's own colors via
  hex codes. Persists across restarts.
- **Lua scripting**, in both the GUI (**Tools > Run script...**) and the
  command line (`--script file.lua`), automate batch conversions, sweep
  settings, render every dither mode for comparison, etc. Full reference
  in [LUA_SCRIPTING.md](LUA_SCRIPTING.md).

Nothing existing was removed or changed in behavior — default settings,
existing presets, and existing palettes all still work exactly as before.

## Building from source

Same dependencies as upstream (just SDL2 — Lua is vendored directly into
`external/lua/`, no separate install needed).

```sh
cd SLK_img2pixel
make          # or: sh linux.sh | make -f -   (regenerates the makefile first)
```

Binaries land in `../bin/`. `mac.sh` and `win_cross.sh` work the same way
for macOS and Windows cross-compilation, respectively (see upstream's
[README.md](README.md) for the general build-script pattern, this fork's
scripts follow the same shape, just with the new source files added).

### A note on `win_cross.sh`

This script hardcodes the original author's own toolchain path
(`/mnt/sdb1/apps/llvm-mingw-...`) — that's a pre-existing upstream quirk,
not something this fork introduced. You'll need to point `CC`/`CXX` at
your own mingw-w64 toolchain if you use it. If you just want a Windows
build without fighting that script, a plain mingw-w64 cross-compile
works fine too — see the "Building on Windows" section in
[MANUAL.md](MANUAL.md).

## What wasn't touched

This repository also contains two other, unrelated programs,
[SLK_make](../SLK_make) (an experimental build system) and `pixtexed` (an
in-progress pixel art / texture editor, not yet listed in the top-level
README). Neither was touched by this fork; they build (or don't) exactly
as they did before. If you want either of those, that's a separate task
from anything here.

## License

Same as upstream: everything except `external/` (third-party code) is
public domain (CC0), see [COPYING](../COPYING). The newly-vendored Lua
interpreter in `external/lua/` is MIT-licensed, same as it is upstream at
[lua.org](https://www.lua.org/license.html).
