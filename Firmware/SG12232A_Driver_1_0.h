/*********************************************************************************
   DRIVER FOR 122x32 SG12232A graphics LCD FROM altronics.com.au
   Using the SED1520 chipset

   Ver 1.0 - Apr 09 - Original version

   Copyright 2009 Geoff Graham - http://geoffg.net
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
   Public License as published by the Free Software Foundation, either version 2 of the License, or (at your
   option) any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
   for more details.  You should have received a copy of the GNU General Public License along with this program.
   If not, see <http://www.gnu.org/licenses/>.
   
   For more details and programming notes go to http://geoffg.net/SG12232A
   
   This code is derived from code for the SED1520 by Radoslaw Kwiecien (en.radzio.dxp.pl)

   Target/Development environment:
    - Microchip PIC microcontroller chips
    - Microchip MPLAB V8 or later
    - CCS C Compiler V4 or later (tested)
    - HiTech C Compiler (not tested)
    
************************************************************************************
    
   This driver exposes the following functions and defines.

   glcd_init()
      * Initialises the display
      * Must be called before any other function.

   glcd_pixel(x,y,colour)
      * Sets the pixel to the given colour.
        - origin (x=0, y=0) is top left corner
        - colour can be ON or OFF (0 or 1)

   glcd_fillScreen(colour)
      * Fills the entire LCD with the given colour.
        - colour can be ON or OFF (0 or 1)

   GLCD_GRAPHICS_WIDTH = 122     Width of display
   GLCD_GRAPHICS_HEIGHT = 32     Height of display

************************************************************************************

    The following pins must be defined */


#ifndef SG12232A_DRIVER_1_0_H_
#define SG12232A_DRIVER_1_0_H_


 #include <stdint.h>
 #include <avr/io.h>
 #include <stdlib.h>
 #include <avr/pgmspace.h>
 
 #ifndef F_CPU
 #define F_CPU 20000000U
 #endif
 #include <util/delay.h>
    
#define SED1520_DATA_PORT 	PORTC
#define SED1520_DATA_DDR 	DDRC
#define SED1520_DATA_PORT_IN 	PINC

#define SED1520_CONTROL_CS_PORT 	PORTD
#define SED1520_CONTROL_CS_DDR 		DDRD
#define SED1520_CS1		(1 << PD5)	// Actif bas
#define SED1520_CS2		(1 << PD6)	// Actif bas

#define SED1520_CONTROL_RESET_PORT 	PORTA
#define SED1520_CONTROL_RESET_DDR 	DDRA
#define SED1520_RES		(1 << PA0)

#define SED1520_CONTROL_OTHER_PORT 	PORTB
#define SED1520_CONTROL_OTHER_DDR 	DDRB
#define SED1520_E		(1 << PB0)
#define SED1520_RW		(1 << PB1)
#define SED1520_A0		(1 << PB2)

#define SED1520_CLK_DDR		DDRD
#define SED1520_CLK_PIN		(1 << PD4)

 

/************************************************************************************/

#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define DISPLAY_START_LINE 0xC0
#define PAGE_ADDRESS_SET 0xB8
#define COLUMN_ADDRESS_SET 0x00
#define ADC_CLOCKWISE 0xA0
#define ADC_COUNTERCLOCKWISE 0xA1
#define STATIC_DRIVE_ON 0xA5
#define STATIC_DRIVE_OFF 0xA4
#define DUTY_RATIO_16 0xA8
#define DUTY_RATIO_32 0xA9
#define READ_MODIFY_WRITE 0xE0
#define END_READ_MODIFY 0xEE
#define RESET 0xE2

#define SCREEN_WIDTH    122
#define SCREEN_HEIGHT 32

void glcd_init(void);
/* Initialises the display
* Must be called before any other function. */

void glcd_pixel(uint8_t x, uint8_t y, uint8_t colour);
/* Sets the pixel to the given colour.
- origin (x=0, y=0) is top left corner
- colour can be ON or OFF (0 or 1) */

void glcd_fillScreen(uint8_t colour);
/* Fills the entire LCD with the given colour.
- colour can be ON or OFF (0 or 1) */


void glcd_WaitForStatus(uint8_t status, uint8_t chip);
void glcd_WriteCommand(uint8_t commandToWrite, uint8_t chip);
void glcd_goto(uint8_t x, uint8_t y);
void glcd_WriteData_XY(uint8_t x, uint8_t y, uint8_t dataToWrite);
void glcd_WriteData_Bulk(uint8_t dataToWrite);
uint8_t glcd_ReadData(uint8_t x, uint8_t y);
void glcd_WriteChar(uint8_t* x_pos, uint8_t* y_pos, char x);
void glcd_WriteString(uint8_t* x_pos, uint8_t* y_pos, char * string);
void glcd_WriteString_P(uint8_t* x_pos, uint8_t* y_pos, const char * string);

#endif