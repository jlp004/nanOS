#include "../libs/vga_io.h"
#include "../libs/serial_io.h"

int main() {
    vga_write("vga!!", 7);
    serial_write("serial!", DEBUG_CODE);
}
