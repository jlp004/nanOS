#include "vga_io.h"

void write(char *buf, unsigned int len) {
    for(unsigned int i = 0; i < len; i++){
        fb_write_cell(i * 2, buf[i], BLUE, GREEN);
    }
    fb_move_cursor(len);
}

void clear(unsigned char fg, unsigned char bg) {
    unsigned short clear_value = (fg & 0x0F) << 12 | (bg & 0x0F) << 8 | (' ');

    for(unsigned int i = 0; i < WIDTH * HEIGHT; i++) {
        ((unsigned short*)FRAMEBUFFER)[i] = clear_value;
    }
}
