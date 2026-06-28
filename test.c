#include <features.h>
#include "semigraphics.h"

const unsigned short* KEYPRESS_ENABLE = 0xfa2d;

/**
Just set some tiles, in the slowest way imaginable
*/
void demo_set_tiles() {
    for(unsigned short y = 0; y < SG_TILES_HEIGHT; ++y) {
        for(unsigned short x = 0; x < SG_TILES_WIDTH; ++x) {
            sg_setchar(x, y, SOLID | COLOUR_3);
        }
    }    

    // Now do some colour cycling
    for(unsigned short y = 0; y < SG_TILES_HEIGHT; ++y) {
        for(unsigned short x = 0; x < SG_TILES_WIDTH; ++x) {
            sg_setpalette(x, y, x == 0 || x == 31 || y == 0 || y == 15);
        }
    }

    // the crashing and looping seems to be MAME specific? VX doesn't do that.

    // interesting corruption happens from this, what is going on? It does it on VX also.
    // seems related to setting the second palette, but how?
}

/**
Draw some SMPTE colour bars, or at least as
close as we can get
*/
void demo_colour_bars() {
    unsigned short x = 2;
    // black the background
    sg_fillchars(0, 0, SG_TILES_WIDTH, SG_TILES_HEIGHT, 0, FALSE);
    // buff bar
    sg_fillchars(x + 0, 0, 4, SG_TILES_HEIGHT - 1, SOLID, TRUE);
    // yellow bar
    sg_fillchars(x + 4, 0, 4, SG_TILES_HEIGHT - 1, COLOUR_1 | SOLID, FALSE);
    // cyan bar
    sg_fillchars(x + 8, 0, 4, SG_TILES_HEIGHT - 1, COLOUR_1 | SOLID, TRUE);
    // green bar
    sg_fillchars(x + 12, 0, 4, SG_TILES_HEIGHT - 1, SOLID, FALSE);
    // magenta bar
    sg_fillchars(x + 16, 0, 4, SG_TILES_HEIGHT - 1, COLOUR_2 | SOLID, TRUE);
    // red bar
    sg_fillchars(x + 20, 0, 4, SG_TILES_HEIGHT - 1, COLOUR_3 | SOLID, FALSE);
    // blue bar
    sg_fillchars(x + 24, 0, 4, SG_TILES_HEIGHT - 1, COLOUR_2 | SOLID, FALSE);
}

void demo_moving_rect() {
    // draw the colour bars so we have something to corrupt
    demo_colour_bars();

    // something is weird with the extents... let's do some math
}

int main() {
    // Disable keyclick sound
    (*KEYPRESS_ENABLE) = 0x00;

    sg_init();
    
    //demo_moving_rect();

    demo_set_tiles();

    return 0;
}