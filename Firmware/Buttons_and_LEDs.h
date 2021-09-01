/*
 * Buttons_and_LEDs.h
 *
 * Created: 2018-05-19 17:10:08
 *  Author: hugo
 */ 

#include <avr/io.h>
#include <stdint.h>

#ifndef BUTTONS_AND_LEDS_H_
#define BUTTONS_AND_LEDS_H_

#define LEDS_PORT		PORTD
#define LED_DDR			DDRD
#define LED_BLUE		(1 << PD2)
#define LED_YELLOW		(1 << PD3)

#define BUTTONS_PORT	PORTA
#define BUTTONS_DDR		DDRA
#define BUTTONS_PORT_IN	PINA
#define BUTTON_1		(1 << PA1)
#define BUTTON_2		(1 << PA2)

typedef enum	{BUTTON_PRESS_1_AND_2	= 0b00000011,
				 BUTTON_PRESS_2			= 0b00000010,
				 BUTTON_PRESS_1			= 0b00000001,
				 NO_BUTTON_PRESS		= 0b00000000} Button_Event_t;		 
extern volatile Button_Event_t Last_Button_Event;

void Buttons_LEDs_Init(void);
uint8_t Buttons_Get_State(void);
void Buttons_Watch_for_Event(volatile Button_Event_t* Button_Event);

void LEDs_Set_State(uint8_t);
uint8_t LEDs_Get_State(void);

#endif /* BUTTONS_AND_LEDS_H_ */