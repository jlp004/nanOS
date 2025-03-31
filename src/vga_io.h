#include "outb_io.h"

#ifndef VGA_IO_H
#define VGA_IO_H

#define BLACK                   0
#define BLUE                    1
#define GREEN                   2
#define CYAN                    3
#define RED                     4
#define MAGENTA                 5
#define BROWN                   6
#define LIGHTGREY               7
#define DARKGREY                8
#define LIGHTBLUE               9
#define LIGHTGREEN              10
#define LIGHTCYAN               11
#define LIGHTRED                12
#define LIGHTMAGENTA            13
#define LIGHTBROWN              14
#define WHITE                   15

#define WIDTH                   80
#define HEIGHT                  25

#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

#define FRAMEBUFFER ((char*)0x000B8000)

/* Writes a character to the VGA frame buffer at 0x000B8000
 * @param i     The location in the frame buffer
 * @param c     The character to be written
 * @param fg    The foreground (character) color
 * @param bg    The background color
 */
static inline void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg){
    FRAMEBUFFER[i] = c;
    FRAMEBUFFER[i+1] = ((fg & 0x0F) << 4 | (bg & 0x0F));
}

void write(char *buf, unsigned int len);
void clear(unsigned char fg, unsigned char bg);

/* Moves the cursor of the frame buffer to the given position. Defined in vga_io.s
 * @param pos   The new position of the cursor
 */
static inline void fb_move_cursor(unsigned short pos) {
    outb(FB_COMMAND_PORT,   FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,      ((pos >> 8) & 0x0FF));
    outb(FB_COMMAND_PORT,   FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,      pos & 0x0FF);
}

#endif
