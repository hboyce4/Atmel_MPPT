/*
 * SG12232A_Driver_1_0.c
 *
 * Created: 2019-04-16 15:32:31
 *  Author: hugo
 */ 

#include "SG12232A_Driver_1_0.h"

const char PROGMEM  font5x7[] = {
	0x00, 0x00, 0x00, 0x00, 0x00,// (space)
	0x00, 0x00, 0x5F, 0x00, 0x00,// !
	0x00, 0x07, 0x00, 0x07, 0x00,// "
	0x14, 0x7F, 0x14, 0x7F, 0x14,// #
	0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
	0x23, 0x13, 0x08, 0x64, 0x62,// %
	0x36, 0x49, 0x55, 0x22, 0x50,// &
	0x00, 0x05, 0x03, 0x00, 0x00,// '
	0x00, 0x1C, 0x22, 0x41, 0x00,// (
	0x00, 0x41, 0x22, 0x1C, 0x00,// )
	0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
	0x08, 0x08, 0x3E, 0x08, 0x08,// +
	0x00, 0x50, 0x30, 0x00, 0x00,// ,
	0x08, 0x08, 0x08, 0x08, 0x08,// -
	0x00, 0x30, 0x30, 0x00, 0x00,// .
	0x20, 0x10, 0x08, 0x04, 0x02,// /
	0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
	0x00, 0x42, 0x7F, 0x40, 0x00,// 1
	0x42, 0x61, 0x51, 0x49, 0x46,// 2
	0x21, 0x41, 0x45, 0x4B, 0x31,// 3
	0x18, 0x14, 0x12, 0x7F, 0x10,// 4
	0x27, 0x45, 0x45, 0x45, 0x39,// 5
	0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
	0x01, 0x71, 0x09, 0x05, 0x03,// 7
	0x36, 0x49, 0x49, 0x49, 0x36,// 8
	0x06, 0x49, 0x49, 0x29, 0x1E,// 9
	0x00, 0x36, 0x36, 0x00, 0x00,// :
	0x00, 0x56, 0x36, 0x00, 0x00,// ;
	0x00, 0x08, 0x14, 0x22, 0x41,// <
	0x14, 0x14, 0x14, 0x14, 0x14,// =
	0x41, 0x22, 0x14, 0x08, 0x00,// >
	0x02, 0x01, 0x51, 0x09, 0x06,// ?
	0x32, 0x49, 0x79, 0x41, 0x3E,// @
	0x7E, 0x11, 0x11, 0x11, 0x7E,// A
	0x7F, 0x49, 0x49, 0x49, 0x36,// B
	0x3E, 0x41, 0x41, 0x41, 0x22,// C
	0x7F, 0x41, 0x41, 0x22, 0x1C,// D
	0x7F, 0x49, 0x49, 0x49, 0x41,// E
	0x7F, 0x09, 0x09, 0x01, 0x01,// F
	0x3E, 0x41, 0x41, 0x51, 0x32,// G
	0x7F, 0x08, 0x08, 0x08, 0x7F,// H
	0x00, 0x41, 0x7F, 0x41, 0x00,// I
	0x20, 0x40, 0x41, 0x3F, 0x01,// J
	0x7F, 0x08, 0x14, 0x22, 0x41,// K
	0x7F, 0x40, 0x40, 0x40, 0x40,// L
	0x7F, 0x02, 0x04, 0x02, 0x7F,// M
	0x7F, 0x04, 0x08, 0x10, 0x7F,// N
	0x3E, 0x41, 0x41, 0x41, 0x3E,// O
	0x7F, 0x09, 0x09, 0x09, 0x06,// P
	0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
	0x7F, 0x09, 0x19, 0x29, 0x46,// R
	0x46, 0x49, 0x49, 0x49, 0x31,// S
	0x01, 0x01, 0x7F, 0x01, 0x01,// T
	0x3F, 0x40, 0x40, 0x40, 0x3F,// U
	0x1F, 0x20, 0x40, 0x20, 0x1F,// V
	0x7F, 0x20, 0x18, 0x20, 0x7F,// W
	0x63, 0x14, 0x08, 0x14, 0x63,// X
	0x03, 0x04, 0x78, 0x04, 0x03,// Y
	0x61, 0x51, 0x49, 0x45, 0x43,// Z
	0x00, 0x00, 0x7F, 0x41, 0x41,// [
	0x02, 0x04, 0x08, 0x10, 0x20,// "\"
	0x41, 0x41, 0x7F, 0x00, 0x00,// ]
	0x04, 0x02, 0x01, 0x02, 0x04,// ^
	0x40, 0x40, 0x40, 0x40, 0x40,// _
	0x00, 0x01, 0x02, 0x04, 0x00,// `
	0x20, 0x54, 0x54, 0x54, 0x78,// a
	0x7F, 0x48, 0x44, 0x44, 0x38,// b
	0x38, 0x44, 0x44, 0x44, 0x20,// c
	0x38, 0x44, 0x44, 0x48, 0x7F,// d
	0x38, 0x54, 0x54, 0x54, 0x18,// e
	0x08, 0x7E, 0x09, 0x01, 0x02,// f
	0x08, 0x14, 0x54, 0x54, 0x3C,// g
	0x7F, 0x08, 0x04, 0x04, 0x78,// h
	0x00, 0x44, 0x7D, 0x40, 0x00,// i
	0x40, 0x80, 0x84, 0x7D, 0x00,// j
	0x00, 0x7F, 0x10, 0x28, 0x44,// k
	0x00, 0x41, 0x7F, 0x40, 0x00,// l
	0x7C, 0x04, 0x18, 0x04, 0x78,// m
	0x7C, 0x08, 0x04, 0x04, 0x78,// n
	0x38, 0x44, 0x44, 0x44, 0x38,// o
	0xFC, 0x14, 0x14, 0x14, 0x08,// p
	0x08, 0x14, 0x14, 0x18, 0x7C,// q
	0x7C, 0x08, 0x04, 0x04, 0x08,// r
	0x48, 0x54, 0x54, 0x54, 0x20,// s
	0x04, 0x3F, 0x44, 0x40, 0x20,// t
	0x3C, 0x40, 0x40, 0x20, 0x7C,// u
	0x1C, 0x20, 0x40, 0x20, 0x1C,// v
	0x3C, 0x40, 0x30, 0x40, 0x3C,// w
	0x44, 0x28, 0x10, 0x28, 0x44,// x
	0x0C, 0x50, 0x50, 0x50, 0x3C,// y
	0x44, 0x64, 0x54, 0x4C, 0x44,// z
	0x00, 0x08, 0x36, 0x41, 0x00,// {
	0x00, 0x00, 0x7F, 0x00, 0x00,// |
	0x00, 0x41, 0x36, 0x08, 0x00,// }
	0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
	0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};

//-------------------------------------------------------------------------------------------------
// Wait for a status bit to come true.  Will wait forever (no timeout)
//-------------------------------------------------------------------------------------------------
void glcd_WaitForStatus(uint8_t status, uint8_t chip) {
	uint8_t tmp;
	
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_A0;                             // select control
	SED1520_DATA_DDR = 0x00;             // and set our port direction
	SED1520_CONTROL_OTHER_PORT |= SED1520_RW;                             // tell the LCD to take control of the data lines
	
	do {
		if(chip == 0)                         // set the chip
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
		else
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;
		
		SED1520_CONTROL_OTHER_PORT |= SED1520_E;
		SED1520_CONTROL_OTHER_PORT &= ~SED1520_A0;                         // this is essentially a nop to provide an access delay
		tmp = SED1520_DATA_PORT_IN;                     // get the status
		SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
		SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2);             // deselect whatever chip was selected in the beginning
	}while(tmp & status);
	
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_RW;                             // tell the LCD to release the data lines
	SED1520_DATA_DDR = 0xFF;            // and set the port direction to output
}


//-------------------------------------------------------------------------------------------------
// Write a command
//-------------------------------------------------------------------------------------------------
void glcd_WriteCommand(uint8_t commandToWrite, uint8_t chip) {
	glcd_WaitForStatus(0x80, chip);
	
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_A0;
	
	SED1520_DATA_PORT = commandToWrite;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_RW;
	
	if(chip == 0)                           // set the chip
	SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
	else
	SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;

	SED1520_CONTROL_OTHER_PORT |= SED1520_E;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_A0;                             // this is essentially a nop to provide an access delay
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2);                 // deselect whatever chip was selected in the beginning
}


//-------------------------------------------------------------------------------------------------
// Position for the next read/write from/to the LCD display memory
// Note that x and y are byte locations, not pixel addresses
//-------------------------------------------------------------------------------------------------
void glcd_goto(uint8_t x, uint8_t y) {
	
	if(x < (SCREEN_WIDTH/2)) {
		glcd_WaitForStatus(0x80, 0);                    // wait for the chip
		glcd_WriteCommand(COLUMN_ADDRESS_SET | x, 0);
		glcd_WriteCommand(PAGE_ADDRESS_SET | y, 0);
	} else {
		glcd_WaitForStatus(0x80, 1);                    // wait for the chip
		glcd_WriteCommand(COLUMN_ADDRESS_SET | (x - (SCREEN_WIDTH/2)), 1);
		glcd_WriteCommand(PAGE_ADDRESS_SET | y, 1);
	}
}


//-------------------------------------------------------------------------------------------------
// Write a data byte
//-------------------------------------------------------------------------------------------------
void glcd_WriteData_XY(uint8_t x, uint8_t y, uint8_t dataToWrite) {

	glcd_goto(x, y);                        // position for the write

	SED1520_CONTROL_OTHER_PORT |= SED1520_A0;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_RW;
	
	SED1520_DATA_PORT = dataToWrite;
	
	if(x < (SCREEN_WIDTH/2)) {           // select the correct chip
	SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
	} else{
	SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;
	}
	
	SED1520_CONTROL_OTHER_PORT |= SED1520_E;                              // strobe the data
	SED1520_CONTROL_OTHER_PORT |= SED1520_A0;                             // this is essentially a nop to provide an access delay
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2);                 // deselect whatever chip was selected in the beginning
	
}


//-------------------------------------------------------------------------------------------------
// Read a data byte from the LCD
//-------------------------------------------------------------------------------------------------
uint8_t glcd_ReadData(uint8_t x, uint8_t y) {
	uint8_t tmp;
	
	glcd_goto(x, y);                        // position for the read
	
	SED1520_CONTROL_OTHER_PORT |= SED1520_A0;                             // select data
	SED1520_DATA_DDR = 0x00;             // and set our port direction
	SED1520_CONTROL_OTHER_PORT |= SED1520_RW;                             // tell the LCD to take control of the data lines
	
	if(x < (SCREEN_WIDTH/2))            // select the correct chip
	SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
	else
	SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;
	
	SED1520_CONTROL_OTHER_PORT |= SED1520_E;                              // for some reason this series of chips needs a dummy read first
	// insert a 100uS delay here if your cpu is faster than 40MHz
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	// insert a 100uS delay here if your cpu is faster than 40MHz
	
	SED1520_CONTROL_OTHER_PORT |= SED1520_E;                              // now the real read
	// insert a 100uS delay here if your cpu is faster than 40MHz
	tmp = SED1520_DATA_PORT_IN;                         // get the data
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_RW;                             // we will take control of the data bus
	SED1520_DATA_DDR = 0xFF;            // and set the port direction accordingly
	SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2);                 // deselect whatever chip was selected in the beginning

	return tmp;
}



//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void glcd_fillScreen(uint8_t colour) {
	char j, i, c;
	if(colour)
	c = 0xff;
	else
	c = 0;
	for(j = 0; j < SCREEN_HEIGHT/8; j++)
	for(i = 0; i < SCREEN_WIDTH; i++) glcd_WriteData_XY(i, j, c);
}


//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void glcd_pixel(uint8_t x, uint8_t y, uint8_t colour) {
	uint8_t temp;
	if(x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) return;
	temp = glcd_ReadData(x, y/8);
	if(colour)
	glcd_WriteData_XY(x, y/8, temp | (1 << (y % 8)));
	else
	glcd_WriteData_XY(x, y/8, temp & ~(1 << (y % 8)));
}



//-------------------------------------------------------------------------------------------------
// Initialise the display
// Only needs to be called once at the start of the program
//-------------------------------------------------------------------------------------------------
void glcd_init(void)
{
	
	SED1520_CLK_DDR |= SED1520_CLK_PIN; /* Set the clock pin as output. MAKE SURE TIMER2 IS INITIALIZED! */

	SED1520_DATA_DDR = 0xFF; /* Set the data port as output */

	SED1520_CONTROL_CS_DDR |= (SED1520_CS2 | SED1520_CS1);
	SED1520_CONTROL_RESET_DDR |= SED1520_RES;
	SED1520_CONTROL_OTHER_DDR |= (SED1520_E | SED1520_RW | SED1520_A0);
	
	// Do the reset for 68 family mode
	
	_delay_ms(10);
	SED1520_CONTROL_RESET_PORT &= ~SED1520_RES;
	_delay_ms(10);
	SED1520_CONTROL_RESET_PORT |= SED1520_RES;
	
	
	uint8_t chip;
	for(chip = 0; chip < 2; chip++) {
		// Setup the chip.  Most commands are not required but are included in case a future version of
		// the LCD will have different defaults.  The only command that is mandatory is DISPLAY_ON.
		glcd_WriteCommand(RESET, chip);
		glcd_WaitForStatus(0x10, chip);
		glcd_WriteCommand(ADC_CLOCKWISE, chip);
		glcd_WriteCommand(STATIC_DRIVE_OFF, chip);
		glcd_WriteCommand(END_READ_MODIFY, chip);
		glcd_WriteCommand(DUTY_RATIO_32, chip);
		glcd_WriteCommand(DISPLAY_ON, chip);                // mandatory
		glcd_WriteCommand(DISPLAY_START_LINE | 0, chip);
	}
	glcd_fillScreen(0);
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

void glcd_WriteChar(uint8_t* x_pos, uint8_t* y_pos, char character)
{
	uint8_t i;
	character -= 32;
	for(i = 0; i < 5; i++) {
		glcd_WriteData_XY(*x_pos, *y_pos, pgm_read_byte(&font5x7[(5 * character) + i]));
		(*x_pos)++;
	}
	glcd_WriteData_XY(*x_pos, *y_pos,0x00);
	(*x_pos)++;
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void glcd_WriteString(uint8_t* x_pos, uint8_t* y_pos, char* string)
{
	while(*string)
	{
		glcd_WriteChar(x_pos, y_pos,*string++);
	}
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void glcd_WriteString_P(uint8_t* x_pos, uint8_t* y_pos, const char * string)
{
	while(pgm_read_byte(string))
	{
		glcd_WriteChar(x_pos, y_pos, pgm_read_byte(string++));
	}
}

//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------

