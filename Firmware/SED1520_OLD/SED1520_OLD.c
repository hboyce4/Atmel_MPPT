//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
#include "SED1520.h"

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
uint8_t lcd_x = 0, lcd_y = 0;
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_Init(void)
{
GLCD_InitPorts();
GLCD_WriteCommand(RESET, 0);
GLCD_WriteCommand(RESET, 1);
GLCD_WaitForStatus(0x10, 0);
GLCD_WaitForStatus(0x10, 1);
GLCD_WriteCommand(DISPLAY_ON, 0);
GLCD_WriteCommand(DISPLAY_ON, 1);
GLCD_WriteCommand(DISPLAY_START_LINE | 0, 0);
GLCD_WriteCommand(DISPLAY_START_LINE | 0, 1);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------


void GLCD_InitPorts(void)
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

}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WaitForStatus(uint8_t status, uint8_t controller)
{
	char tmp;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_A0; /* A0 = 0 -> Command Mode */
	SED1520_DATA_DDR = 0x00; /* Data port as input */
	SED1520_CONTROL_OTHER_PORT |= SED1520_RW; /* RW = 1 -> Read Mode */

	do
	{
		if(controller == 0) /* Set appropriate CS line to zero */
		{
			SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
		}
		else
		{
			SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;
		}
		
		SED1520_CONTROL_OTHER_PORT |= SED1520_E;
		asm("nop");asm("nop");
		tmp = SED1520_DATA_PORT_IN;
		SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;		
		
		SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2); /* Set both CS lines to one */
		
		
	}while(tmp & status);
	
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_RW; /* RW = 0 -> Write Mode */
	SED1520_DATA_DDR = 0xFF; /* Data port as output */
}
//-------------------------------------------------------------------------------------------------
// Write command
//-------------------------------------------------------------------------------------------------
void GLCD_WriteCommand(uint8_t commandToWrite,uint8_t ctrl)
{
	GLCD_WaitForStatus(0x80, ctrl);

	SED1520_CONTROL_OTHER_PORT &= ~SED1520_A0;
	
	SED1520_DATA_PORT = commandToWrite;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_RW;



	if(ctrl)
	{
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
	}
	else
	{
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;
	}
	
	SED1520_CONTROL_OTHER_PORT |= SED1520_E;
	asm("nop");asm("nop");
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	
	SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2); /* Set both CS lines to one */
	
}
//-------------------------------------------------------------------------------------------------
// Write data
//-------------------------------------------------------------------------------------------------
void GLCD_WriteData(uint8_t dataToWrite)
{
	GLCD_WaitForStatus(0x80, 0);
	GLCD_WaitForStatus(0x80, 1);
	SED1520_CONTROL_OTHER_PORT |= SED1520_A0;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_RW;
	SED1520_DATA_PORT = dataToWrite;
	
	if(lcd_x < SCREEN_WIDTH/2)
	{
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
	}
	else
	{
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;
	}
	
	SED1520_CONTROL_OTHER_PORT |= SED1520_E;
	asm("nop");asm("nop");
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	
	SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2); /* Set both CS lines to one */
	
	lcd_x++;
	if(lcd_x >= SCREEN_WIDTH)
	lcd_x = 0;
}
//-------------------------------------------------------------------------------------------------
// Read data
//-------------------------------------------------------------------------------------------------
uint8_t GLCD_ReadData(void)
{
	uint8_t tmp;

	GLCD_WaitForStatus(0x80, 0);
	GLCD_WaitForStatus(0x80, 1);
	SED1520_CONTROL_OTHER_PORT |= SED1520_A0;
	SED1520_CONTROL_OTHER_PORT |= SED1520_RW;
	SED1520_DATA_DDR = 0x00;
	SED1520_DATA_PORT = 0xFF;
	
	if(lcd_x < SCREEN_WIDTH/2)
	{
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS1;
	}
	else
	{
		SED1520_CONTROL_CS_PORT &= ~SED1520_CS2;
	}
	
	SED1520_CONTROL_OTHER_PORT |= SED1520_E;
	asm("nop");asm("nop");
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	asm("nop");asm("nop");
	SED1520_CONTROL_OTHER_PORT |= SED1520_E;
	asm("nop");asm("nop");
	tmp = SED1520_DATA_PORT_IN;
	SED1520_CONTROL_OTHER_PORT &= ~SED1520_E;
	
	SED1520_CONTROL_CS_PORT |= (SED1520_CS1|SED1520_CS2); /* Set both CS lines to one */
	
	
	SED1520_DATA_DDR = 0xFF;
	lcd_x++;
	if(lcd_x > 121)
	lcd_x = 0;
	return tmp;
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_GoTo(uint8_t x,uint8_t y)
{
lcd_x = x;
lcd_y = y;




if(x < (SCREEN_WIDTH/2))
  {
	GLCD_WaitForStatus(0x80, 0);
  GLCD_WriteCommand(COLUMN_ADDRESS_SET | lcd_x, 0);
  GLCD_WriteCommand(PAGE_ADDRESS_SET | lcd_y, 0);
  /*GLCD_WriteCommand(COLUMN_ADDRESS_SET | 0, 1);
  GLCD_WriteCommand(PAGE_ADDRESS_SET | lcd_y, 1);*/
  }
else
  {
	  GLCD_WaitForStatus(0x80, 1);
  GLCD_WriteCommand(COLUMN_ADDRESS_SET | (lcd_x - (SCREEN_WIDTH/2)), 1);
  GLCD_WriteCommand(PAGE_ADDRESS_SET | lcd_y, 1);
  }
}
//-------------------------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------------------------
void GLCD_ClearScreen(void)
{
char j, i;
for(j = 0; j < 4; j++)
  {
  GLCD_GoTo(0, j);
  for(i = 0; i < SCREEN_WIDTH; i++)
    {
	GLCD_WriteData(0);
	}
  }
GLCD_GoTo(0, 0);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteChar(char x)
{
	char i; 
	x -= 32; 
	for(i = 0; i < 5; i++) {
		GLCD_WriteData(pgm_read_byte(&font5x7[(5 * x) + i]));
	}
	GLCD_WriteData(0x00);
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteString(char * string)
{
while(*string)
  {
  GLCD_WriteChar(*string++);
  }
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_WriteString_P(const char * string)
{
	while(pgm_read_byte(string))
	{
		GLCD_WriteChar(pgm_read_byte(string++));
	}
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_SetPixel(uint8_t x, uint8_t y, LCD_Color_t Color)
{
uint8_t temp;  
GLCD_GoTo(x, y/8); 
temp = GLCD_ReadData(); 
GLCD_GoTo(x, y/8); 
if(Color)
  GLCD_WriteData(temp | (1 << (y % 8))); 
else
  GLCD_WriteData(temp & ~(1 << (y % 8))); 
}
//-------------------------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------------------------
void GLCD_Bitmap(char * bmp, uint8_t x, uint8_t y, uint8_t dx, uint8_t dy)
{
uint8_t i, j;
for(j = 0; j < dy / 8; j++)
  {
  GLCD_GoTo(x,y + j);
  for(i = 0; i < dx; i++)
    GLCD_WriteData(pgm_read_byte(bmp++)); 
  }
}

