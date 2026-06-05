#include "defines.h"
#include "semigraphics.h"

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

void sg_setpixel(unsigned char x, unsigned char y, BOOL value) {
    // TODO: Table to identify specific pixel (x/2, y/3) likely faster than this
    unsigned short tileIdx = (y/3) * SG_TILES_WIDTH + (x/2);
    
    // Table to get the bit shift for a specific bit of the tile
    const unsigned char bitShifts[3][2] = {
        // Y % 3 == 0 (0, 3, 6, etc.)
        { 5, 4 }, // top left, top right
        // Y % 3 == 1 (1, 4, 7, etc.)
        { 3, 2 }, // middle left, middle right
        // Y % 3 == 2 (2, 5, 8, etc.)
        { 1, 0 } // lower left, lower right
    };

    unsigned char c = tiles[tileIdx];
    unsigned char shift = bitShifts[y % 3][x % 2];
    
    // Flip only the bit
    if(value) {
        tiles[tileIdx] |= (1 << shift);
    }
    else {
        tiles[tileIdx] &= ~(1 << shift);
    }
}

void sg_fillchars(unsigned char x, unsigned char y, unsigned char width, unsigned char height, enum sg_char c, BOOL second_palette) {
    // FIXME: something is wrong here, i'm running into user memory...
    for(unsigned short j = y; j < y + height; ++j) {
        unsigned short row = j * SG_TILES_WIDTH;

        for(unsigned short i = x; i < x + width; ++i) {
            tiles[row + i] = c;
            // for now, also set palette
            attributes[row + i] = second_palette ? 0x62 : 0x60;
        }
    }
}

enum sg_char sg_peekchar(unsigned char x, unsigned char y) {
    return tiles[y * SG_TILES_WIDTH + x];
}

BOOL sg_peekpalette(unsigned char x, unsigned char y) {
    return attributes[y * SG_TILES_WIDTH + x] == 0x62;
}