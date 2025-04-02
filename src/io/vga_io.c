#include "../libs/vga_io.h"
#include "../libs/serial_io.h"

unsigned int cursor_pos = 0;


void vga_write(char *buf, unsigned int len) {
    if(len > 1000) {
        return;
    }

    for(unsigned int i = cursor_pos; i < len; i++){
        fb_write_cell(i * 2, buf[i], BLUE, GREEN);
        if(i > WIDTH * HEIGHT) {
            i %= WIDTH * HEIGHT;
            len -= WIDTH * HEIGHT;
        }
    }

    fb_move_cursor(len);
    cursor_pos += len;
    cursor_pos %= WIDTH * HEIGHT;
}

void vga_clear(unsigned char fg, unsigned char bg) {
    unsigned short clear_value = (fg & 0x0F) << 12 | (bg & 0x0F) << 8 | (' ');

    for(unsigned int i = 0; i < WIDTH * HEIGHT; i++) {
        ((unsigned short*)FRAMEBUFFER)[i] = clear_value;
    }
}
