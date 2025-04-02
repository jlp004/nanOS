#include "libs/vga_io.h"
#include "libs/serial_io.h"
#include "libs/bool.h"

int main() {
    vga_write("vga!!", 5);
    vga_write("next string!!", 13);
    serial_configure_fifo(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE, TRUE);
    serial_write("serial!", DEBUG_CODE);
}
