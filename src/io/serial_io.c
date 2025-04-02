#include "../libs/serial_io.h"
#include "../libs/vga_io.h"
#include "../libs/bool.h"


#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)     (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)       (base + 5)
#define EMPTY                               1

/* serial_configure_baud_rate:
 * Sets the speed of the data being sent. Default speed is 115200 bits/s,  
 * The parameter is the divisor, so final speed is (115200 / divisor) bits/s
 * 
 * @param com       The COM port to configure
 * @param divisor   The divisor
 */
static void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0xFF);
    outb(SERIAL_DATA_PORT(com), divisor & 0xFF);
}

/* serial_configure_line
 * Configures the line of the given serial port. The port is set to have data length of 8 bits, no parity bits,
 * 1 stop bit, and break control disabled
 * 
 * @param com       The Serial port to configure
 */
static void serial_configure_line(unsigned short com) {
    /*    
     *  Bit:        | 7 | 6 | 5 4 3 | 2 | 1 0 |
     *  Content:    | d | b | prty  | s | dl  |
     *  Value:      | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
    */
   outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/* serial_configure_fifo
 * Enables fifo queue, clears queues, uses 14 bytes as queue size
 * 
 */
void serial_configure_fifo(unsigned short com) {
    /*
     * Bits: 7  6 | 5 | 4 | 3 | 2 | 1 | 0
     *       lvl    bs  r  dma clt clr  e
     *       1  1   0   0   0   1   1   1 = 0xC7
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/* serial_configure_modem
 * Opens DTR and RTS pins to allow data to flow through the serial port
 */
void serial_configure_modem(unsigned short com, _bool status) {
    if(status == TRUE) {
        outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
    }
    else {
        outb(SERIAL_MODEM_COMMAND_PORT(com), 0x00);
    }
}

/* serial_is_transmit_fifo_empty
 * Checks wheter the current transmit FIFO queue is empty for the given COM port
 *
 * @param com   The COM port
 * @return      0 if the transmit FIFO queue is not empty
 * @return      1 if the transmit FIFO queue is empty
 */
static int serial_is_transmit_fifo_empty(unsigned short com) {
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/* serial_write:
 * write to a serial port a given char buff up to 1000 chars, includes a code to signify the type of msg
 *
 * 
 */
void serial_write(char *buf, unsigned int code) {
    if(!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE)) {
        vga_write("SERIAL IS NOT CLEAR", 20);
        return;
    }
    

    serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
    serial_configure_line(SERIAL_COM1_BASE);

    switch(code){
        case ERR_CODE:
            outb(SERIAL_COM1_BASE, 'E');
            outb(SERIAL_COM1_BASE, 'R');
            outb(SERIAL_COM1_BASE, 'R');
            outb(SERIAL_COM1_BASE, 'O');
            outb(SERIAL_COM1_BASE, 'R');
            outb(SERIAL_COM1_BASE, ':');
            outb(SERIAL_COM1_BASE, ' ');
            break;
        case INFO_CODE:
            outb(SERIAL_COM1_BASE, 'I');
            outb(SERIAL_COM1_BASE, 'N');
            outb(SERIAL_COM1_BASE, 'F');
            outb(SERIAL_COM1_BASE, 'O');
            outb(SERIAL_COM1_BASE, ':');
            outb(SERIAL_COM1_BASE, ' ');
            break;
        case DEBUG_CODE:
            outb(SERIAL_COM1_BASE, 'D');
            outb(SERIAL_COM1_BASE, 'E');
            outb(SERIAL_COM1_BASE, 'B');
            outb(SERIAL_COM1_BASE, 'U');
            outb(SERIAL_COM1_BASE, 'G');
            outb(SERIAL_COM1_BASE, ':');
            outb(SERIAL_COM1_BASE, ' ');
        default:
            
    }


    for(int i = 0; i < 1000; i++) {
        if(buf[i] != '\0') {
            outb(SERIAL_COM1_BASE, (unsigned short)(buf)[i]);
        }
        else {
            outb(SERIAL_COM1_BASE, (unsigned short)('\n'));
            break;
        }
    }
}