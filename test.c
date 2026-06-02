#include <features.h>
#include "semigraphics.h"

const unsigned short* KEYPRESS_ENABLE = 0xfa2d;

int main() {
    // Disable keyclick sound
    (*KEYPRESS_ENABLE) = 0x00;

    sg_init();

    while(1) {

    }

    return 0;
}