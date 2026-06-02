#include "defines.h"
#include "semigraphics.h"

// TODO: Confirm these addresses
unsigned char* attributes = 0xc000;
unsigned char* tiles = 0xc200; // attributes plus 512 bytes

void sg_init() {
    // Clear memory
    sg_clear(SOLID);
}

void sg_clear(enum sg_char fill) {
    // Reset palette
    for(unsigned int i = 0; i < SG_TILES_WIDTH * SG_TILES_HEIGHT; ++i) {
        attributes[i] = 0x60;
    }

    // Reset contents of screen RAM
    for(unsigned int i = 0; i < SG_TILES_WIDTH * SG_TILES_HEIGHT; ++i) {
        tiles[i] = fill;
    }
}

void sg_setpalette(unsigned char x, unsigned char y, BOOL second_palette) {
    attributes[y * SG_TILES_WIDTH + x] = second_palette ? 0x62 : 0x60;
}

void sg_setchar(unsigned char x, unsigned char y, enum sg_char c) {
    tiles[y * SG_TILES_WIDTH + x] = c;
}