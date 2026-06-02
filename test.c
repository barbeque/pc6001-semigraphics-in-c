#include <features.h>
#include "semigraphics.h"

const unsigned short* KEYPRESS_ENABLE = 0xfa2d;

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

    // start running in the 90s
    enum sg_char last_char = sg_peekchar(0, 0);
    BOOL last_pal = sg_peekpalette(0, 0);
    unsigned char i = 0;
    unsigned char j = 0;

    while(1) {
        // restore previous character
        sg_setchar(i, j, last_char);
        sg_setpalette(i, j, last_pal);

        // increment position
        i += 1;
        if(i >= 32) {
            j += 1;
            i = 0;
            if(j >= 16) {
                j = 0;
            }
        }

        // remember the character that was at the new position
        last_char = sg_peekchar(i, j);
        last_pal = sg_peekpalette(i, j);

        // overwrite it
        sg_setchar(i, j, COLOUR_3 | SOLID); // always red! always red!
        sg_setpalette(i, j, FALSE);
    }
}

int main() {
    // Disable keyclick sound
    (*KEYPRESS_ENABLE) = 0x00;

    sg_init();
    
    demo_moving_rect();

    return 0;
}