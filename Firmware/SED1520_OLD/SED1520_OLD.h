// jm12232.h
//
//
#include <avr/pgmspace.h>
#include <avr/io.h>
//#include "font.h"


#ifndef F_CPU
#define F_CPU 20000000U
#endif
#include <util/delay.h>


#define SCREEN_WIDTH	122
#define SCREEN_HEIGHT	32

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


typedef enum {
	
	BLACK = 0,
	WHITE = 1
	
} LCD_Color_t;


void GLCD_Init(void);

void GLCD_InitPorts(void);
void GLCD_WaitForStatus(uint8_t,uint8_t);
void GLCD_WriteCommand(uint8_t,uint8_t);
void GLCD_WriteData(uint8_t);
uint8_t GLCD_ReadData(void);
void GLCD_GoTo(uint8_t,uint8_t);
void GLCD_ClearScreen(void);
void GLCD_WriteChar(char);
void GLCD_WriteString(char *);
void GLCD_WriteString_P(const char *);
void GLCD_SetPixel(uint8_t, uint8_t, LCD_Color_t);
void GLCD_Bitmap(char * , uint8_t, uint8_t, uint8_t, uint8_t);

