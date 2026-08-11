/*
SLK_img2pixel - a tool for converting images to pixelart

Shared multi-frame GIF reader - decodes every frame of a (possibly
animated) GIF into a plain array of Image32, for the rest of the
pipeline (blur/sample/dither/etc, all of which already work on Image32)
to process exactly like any other input image.

Written in 2026, released to the public domain (CC0), same terms as the
rest of this project - see COPYING.
*/

#ifndef _SLK_GIF_READ_H_

#define _SLK_GIF_READ_H_

#include "image.h"

//Decodes every frame of the GIF file at 'path'.
//On success (returns 1):
//  *out_frames     - malloc'd array of *out_frame_count Image32* pointers.
//                    Caller must free each Image32* and then the array.
//  *out_frame_count
//  *out_delays_cs  - malloc'd array of *out_frame_count delays, in
//                    hundredths of a second (GIF's native delay unit).
//                    Caller must free. Pass NULL if not needed.
//On failure (bad path, not a GIF, decode error) returns 0 and leaves the
//output parameters untouched.
int SLK_gif_read_all_frames(const char *path, Image32 ***out_frames, int *out_frame_count, int **out_delays_cs);

#endif
