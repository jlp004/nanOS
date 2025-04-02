#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#include "bool.h"

/* I/O ports */

#define SERIAL_COM1_BASE    0x3F8   
#define ERR_CODE            1
#define INFO_CODE           2
#define DEBUG_CODE          3
#define NONE                4

/* I/O Port Commands */
/* Tells the port to expect the highest 8 bits, then the lowest 8 bits will follow */
#define SERIAL_LINE_ENABLE_DLAB             0x80

extern void outb(unsigned short port, unsigned char data);
extern unsigned char inb(unsigned short port);
void serial_write(char *buf, unsigned int code);
void serial_configure_fifo(unsigned short com);
void serial_configure_modem(unsigned short com, _bool status);


#endif
