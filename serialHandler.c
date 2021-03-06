/* The Serial Handler module handles the serial port logic for the
 * Led flasher bare metal application, and depends on the general
 * serial module. The serial module must be initialized before. */

#include "ledFlasher.h"
#include "wdtimer.h"
#include "consoleUtils.h"
#include <stdint.h>

/******************************************************************************
 **              HELPER FUNCTION PROTOTYPES
 ******************************************************************************/

static void SerialHandler_displayHelpMenu(void);

/******************************************************************************
 **              SERIAL PORT HANDLING
 ******************************************************************************/
static volatile uint8_t s_rxByte = 0;
void SerialHandler_notifyOnSerialRxIsr(uint8_t rxByte) {
	s_rxByte = rxByte;
}

void SerialHandler_doBackgroundWork(void)
{
	if (s_rxByte != 0) {
		if (s_rxByte == '?') {
			SerialHandler_displayHelpMenu();
		} else if (s_rxByte >= '0' && s_rxByte <= '9'){
			LedFlasher_setSpeed(s_rxByte - '0');
            ConsoleUtilsPrintf("\nSetting LED speed to %c\n", s_rxByte);
		} else if (s_rxByte == 'x') {
			Watchdog_stopHitting();
            ConsoleUtilsPrintf("\nNo longer hitting the watchdog.\n", s_rxByte);
		} else {
			ConsoleUtilsPrintf("\nMust enter valid command\n");
			SerialHandler_displayHelpMenu();
		}

		s_rxByte = 0;
	}
}

static void SerialHandler_displayHelpMenu(void)
{
    ConsoleUtilsPrintf("\nCommands:\n"
        "?   : Display this help message\n"
        "0-9 : Set speed 0 (slow) to 9 (fast)\n"
        "x   : Stop hitting the watchdog\n"
        "JOY : Up (faster), Down (slower)\n");
}
