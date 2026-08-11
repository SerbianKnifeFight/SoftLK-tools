/*
SLK_img2pixel - a tool for converting images to pixelart

Minimal animated GIF writer, added to support GIF output of img2pixel's
own indexed (palette + 8-bit index buffer) dithering results directly,
without re-quantizing/re-dithering the image a second time.

Written in 2026, released to the public domain (CC0), same terms as the
rest of this project - see COPYING.
*/

#ifndef _SLK_GIF_H_

#define _SLK_GIF_H_

#include <stdint.h>

//width,height: dimensions of every frame (all frames must share the same size)
//palette: RGBA colors, using the same color32() layout as the rest of SLK_img2pixel
//         (r in the lowest byte, a in the highest); alpha is ignored for the GIF
//         color table itself.
//palette_size: number of used entries in 'palette' (<=256)
//frames: array of 'frame_count' pointers, each pointing to width*height uint8_t
//        palette indices (this is exactly what Image8::data already is)
//delays_cs: array of 'frame_count' delay values, in hundredths of a second
//           (GIF's native time unit). Ignored (may be NULL) if frame_count==1
//loop: nonzero to loop the animation forever, 0 to play once
//transparent_index: palette index to mark as transparent, or -1 to disable
//                    transparency (SLK_img2pixel uses index 0 for
//                    below-alpha-threshold pixels, so pass 0 to keep
//                    holes in the source image transparent in the GIF)
//
//Returns 1 on success, 0 on failure (bad arguments or file I/O error)
int SLK_gif_write(const char *path, int width, int height,
                   const uint32_t *palette, int palette_size,
                   uint8_t *const *frames, int frame_count,
                   const int *delays_cs, int loop, int transparent_index);

#endif
