# SLK_img2pixel Manual

This is the full guide for this fork of SLK_img2pixel. It covers the original tool's features plus everything added in this fork: new dither algorithms, GIF import and export, a custom UI theme, and Lua scripting.

If you just want a quick list of what's different from the upstream project, check out FORK_README.md instead. This document walks through how to actually use the app.

There are two programs:

- **SLK_img2pix**, the windowed app with a live preview.
- **SLK_img2pix_cmd**, the command-line version, meant for automation and scripting. It uses the same engine, just without a preview window.

---

## 1. The basics

Open SLK_img2pix and either drag an image onto the window or use Load > Image. The tab strip on the right (Sample, Dither, Palette, Colors, Theme) controls how your image gets turned into pixel art, and any changes you make show up in the live preview right away. Once you're happy with the result, go to Save > Image and choose a filename. Whatever extension you type decides the output format: .png, .bmp, .tga, .pcx, or .gif.

Supported input formats: PNG, GIF (all frames, see section 4), BMP, JPEG, and TGA.

### Sample tab

This tab controls the resolution of your pixel art and how the source image gets downscaled to reach it.

| Control | What it does |
|---|---|
| Absolute / Relative | Absolute lets you set an exact output size in pixels. Relative sets the output size as a fraction of the input size (for example, dividing by 4 turns a 512px image into 128px). |
| Width / Height (absolute) | The exact output dimensions. |
| Scale X / Scale Y (relative) | The divisor applied to the input size. |
| Sample mode | The filter used for downscaling: Nearest, Bilinear, Bicubic, Lanczos, or Cluster. Cluster is a dithering-aware downsampler and is usually the best choice for pixel art. |
| Sample x/y offset | Shifts the sampling grid, useful for fine-tuning exactly which pixels get sampled. |
| Blur amount | Applies a gaussian blur before downsampling, which softens the image so it doesn't alias as badly. |
| Sharpen amount | Applies unsharp-mask sharpening before downsampling. |

### Dither tab

This tab controls how the large set of source colors gets reduced down to your target palette.

| Control | What it does |
|---|---|
| Alpha threshold | Pixels with alpha below this value become fully transparent in the output. |
| Distance metric | How "distance" between two colors is measured when picking the closest palette entry. Options are RGB Euclidian, RGB Weighted, RGB Redmean, CIE76, CIE94, and CIEDE2000. The LAB-space metrics (the CIE ones) generally match human color perception better, at the cost of more CPU time. |
| Dither/Assignment mode | See the table below for all the options. |
| Dither amount | Only applies to ordered dithering modes. Controls how strong the dither pattern is. |

Available dither modes:

| Mode | Kind | Notes |
|---|---|---|
| None | closest-color | No dithering, just flat color banding. |
| Bayer 8x8 / 4x4 / 2x2 | ordered | The classic ordered dithering. A larger matrix gives smoother gradients but a more visible repeating pattern. |
| Bayer 5x5 / 3x3 (new) | ordered | A non-power-of-two ordered dither, built as an evenly dispersed dot pattern instead of the classic recursive Bayer construction (which only works for power-of-two sizes). Handy when 4x4 feels too coarse and 8x8 too fine. |
| Cluster 8x8 / 4x4 | ordered | Clustered-dot ordered dithering. Clumps dots together instead of spreading them out, giving a halftone-print look. |
| Floyd-Steinberg / Floyd-Steinberg 2 | error diffusion | The classic error-diffusion dither. The "2" version is a simplified, faster variant. |
| Stucki (new) | error diffusion | Uses a wider error-diffusion kernel than Floyd-Steinberg, so it gives smoother gradients with less visible directional artifacting. |
| Burkes (new) | error diffusion | Similar to Stucki but with a cheaper 2-row kernel. A middle ground between Floyd-Steinberg and Stucki. |
| Sierra (new) | error diffusion | Another wide-kernel diffusion dither, similar quality to Stucki. |
| Sierra Two-Row (new) | error diffusion | A cheaper 2-row version of Sierra. |
| Sierra Lite (new) | error diffusion | A very cheap 3-tap diffusion kernel. The fastest of the diffusion dithers, with slightly lower quality. |
| Median-Cut | palette assignment | Not really a dither. It assigns colors using median-cut bucketing. |
| PicoCAD (new) | special | Mimics the shading trick from the picoCAD 3D tool. Instead of a full dither pattern, it uses a single fixed checkerboard to blend between the two closest palette colors. Gives a distinctive "retro low-color 3D render" look rather than a photographic dither. |

### Palette tab

- The Red, Green, and Blue sliders edit whichever palette color is currently selected. Click a swatch to select it.
- Color count sets how many entries are in the palette.
- Generate palette runs k-means clustering on the current processed image to automatically pick a palette. The k-means++ toggle turns on a smarter (but slower) seeding method for that clustering.
- Load > Palette and Save > Palette read and write palette files: .gpl, .png, .hex, .pal, and a few other formats.

### Colors tab

Post-processing color adjustments that get applied before dithering: Brightness, Contrast, Saturation, Hue, Gamma, and a red/green/blue Tint that's multiplied over the whole image.

### Theme tab (new)

This customizes the app's own UI colors. It has nothing to do with your image, it's purely cosmetic for the app window itself.

- Presets: Default (the original look), Dark, Light, and Pink, each one click away.
- Custom colors: five fields, each a 6-digit hex code (RRGGBB) you edit directly:
  - Background, the flat fill behind most widgets
  - Border/shadow, widget outlines and pressed-state shading
  - Bevel (dark) and Bevel (light), the two halves of the 3D bevel edge every button and slider has
  - Text, the label and button text color

Type a new value and press Enter to apply it live. Whatever you set gets remembered and reloaded automatically the next time you open the app.

### Presets (JSON)

Load > Preset and Save > Preset save all of the settings above (sample, dither, palette, and colors, but not the theme, which is kept separate) to a JSON file. That way you can reuse a full configuration later, share it with someone, or use it with the command-line tool via --preset.

### Batch processing

Tools > Batch processes every image in a folder using your current settings, writing the results to another folder. It's a good option for converting a whole folder of source images at once without needing to write a script.

---

## 2. GIF import and export (new)

Both SLK_img2pix and SLK_img2pix_cmd can read and write animated GIFs, decoding and encoding every frame, not just the first one.

- **Import**: drag a .gif onto the window, or use Load > Image and pick one. Every frame gets decoded. The live preview only shows frame 1, but all the frames are kept.
- **Export**: use Save > Image and type (or pick) a filename ending in .gif. If your input was itself an animated GIF, every frame gets processed with your current settings and re-encoded as a new animated GIF, using one shared palette so the whole animation stays consistent. If the input wasn't animated, you'll still get a single-frame GIF out, so this also works as a plain "export as GIF" option for any image.

Frame timing (the delay per frame) is preserved from the source GIF.

On the command line, all of this happens automatically based on file extensions. `--in foo.gif --out bar.gif` just works.

---

## 3. Lua scripting (new)

Both programs can run Lua scripts for automation: looping over many files, rendering the same image in every dither mode, picking settings based on a filename, and so on. See section 4 below for the full API and some worked examples.

- **Command line**: `SLK_img2pix_cmd --script myscript.lua`
- **GUI**: Tools > Run script..., pick a .lua file, then click Run. Anything the script prints with `print()` shows up in the window, since there's no console to print to otherwise.

---

## 4. Lua API reference

See LUA_SCRIPTING.md for the full API reference, worked examples, and notes on what scripting is (and isn't) good for.

---

## 5. Command-line reference (SLK_img2pix_cmd)

```
SLK_img2pix_cmd --in filename --out filename [--preset preset]
   --in                 image file to process (image or .gif)
   --out                output file (image or .gif)
   --outp                output palette
   --dump-defaults       write default preset to stdout
   --gen COLORS          generate a COLORS-entry color palette via k-means
   --preset              JSON preset file to use for processing
   --script              run a Lua script instead of a single --in/--out job
   --help                print this text
```

A typical single-shot conversion looks like this:

```sh
SLK_img2pix_cmd --in photo.png --out pixelart.png --preset my_settings.json
```

And you can dump the current defaults to a preset file, then edit it by hand:

```sh
SLK_img2pix_cmd --dump-defaults > default.json
```

---

## 6. Where things are stored

- **settings.json** (next to the executable): your window's remembered file-dialog paths, GUI scale, and theme colors. Delete it if you want to reset the app back to a first-run state.
- **default.json** (next to the executable): loaded automatically on startup if it's present. This is what "Load default preset on launch" actually means in practice.
