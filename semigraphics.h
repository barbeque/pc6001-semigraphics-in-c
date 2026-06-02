#ifndef _SEMIGRAPHICS_H_
#define _SEMIGRAPHICS_H_

#include "defines.h"

/**
Library support for the PC-6001 semigraphics mode.

Citations:
 - https://000.la.coocan.jp/p6/tech.html#vram
*/

// Each tile is 2x3 "pixels," so this is really 64 x 48 pixels
#define SG_TILES_WIDTH 32
#define SG_TILES_HEIGHT 16

/**
Flags for semigraphics characters
*/
enum sg_char {
    // Top 2 bits decide which of the four colours you want
    COLOUR_0 = 0x00,
    COLOUR_1 = 0x80,
    COLOUR_2 = 0x40,
    COLOUR_3 = 0xC0,
    // Bottom six bits decide which pixels are lit
    TOP_LEFT = 0x20,
    TOP_RIGHT = 0x10,
    MIDDLE_LEFT = 0x08,
    MIDDLE_RIGHT = 0x04,
    BOTTOM_LEFT = 0x02,
    BOTTOM_RIGHT = 0x01,
    // Convenience definitions
    SOLID = 0x3f,
    CLEAR = 0x00
};

/**
Start 9-colour semigraphics mode (Semigraphics 4; Screen Mode 2)
*/
void sg_init();

/**
Clear (or fill) the screen, resetting attributes
*/
void sg_clear(enum sg_char fill);

/**
Set the palette for an individual character tile.

If false, it will use the default $60 palette (Green, Yellow, Blue, Red)
If true, it will use the $62 palette (White/Buff, Cyan, Magenta, Orange)
*/
void sg_setpalette(unsigned char x, unsigned char y, BOOL second_palette);

/**
Set the status of a character on the screen.
*/
void sg_setchar(unsigned char x, unsigned char y, enum sg_char c);

#endif