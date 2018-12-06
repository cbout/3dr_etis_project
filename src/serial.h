#ifndef _SERIAL_
#define _SERIAL_
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <mavlink.h>
#include "mavlink_perso_types.h"

void open_serial(int* fd, char* uart_name, int baudrate, int* status);

int open_port(const char* port);

int setup_port(int fd, int baud, int data_bits, int stop_bits, int parity, int hardware_control);

int read_message(mavlink_message_t* message, int fd);
#endif