/* The Serial Handler module handles the background serial port logic for the
 * Led flasher bare metal application, and depends on the general
 * serial module and its Rx interrupt service routine. */

#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "led.h"
#include "watchdog.h"
#include <stdint.h>
void SerialHandler_notifyOnSerialRxIsr(uint8_t rxByte);
void SerialHandler_doBackgroundWork(void);
#endif