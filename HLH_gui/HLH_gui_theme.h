/*
HLH_gui - a small immediate-mode-ish gui library

Theme support: every widget originally drew itself with a handful of
hardcoded 0xAARRGGBB literals. This pulls those into one small struct so
a whole app can be recolored by changing five values, instead of hunting
through every widget's draw function.

Written in 2026, released to the public domain (CC0), same terms as the
rest of this project - see COPYING.
*/

#ifndef _HLH_GUI_THEME_H_

#define _HLH_GUI_THEME_H_

#include <stdint.h>

typedef struct
{
   uint32_t bg;          //flat widget fill (button/slider/group background, etc.)
   uint32_t border;       //widget outline/drop-shadow
   uint32_t bevel_dark;    //dark half of the 3D bevel edge
   uint32_t bevel_light;   //light half of the 3D bevel edge
   uint32_t text;          //label/button/menu text and glyph ink
}HLH_gui_theme;

//The theme every widget's draw function reads from. Change its fields (or
//assign a whole new HLH_gui_theme to it) at any time, including mid-session
//- the next redraw will pick it up, no restart needed.
extern HLH_gui_theme HLH_gui_theme_current;

//Resets HLH_gui_theme_current to the library's original look (the exact
//colors every widget used to have hardcoded).
void HLH_gui_theme_set_default(void);

#endif
