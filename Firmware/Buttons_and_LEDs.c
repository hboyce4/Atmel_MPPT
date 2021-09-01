/*
 * Buttons_and_LEDs.c
 *
 * Created: 2018-05-19 17:20:33
 *  Author: hugo
 */ 
#include "Buttons_and_LEDs.h"

/* Initialise les pins des boutons et des LEDs */
void Buttons_LEDs_Init(void){
	
	LED_DDR |= (LED_BLUE |LED_YELLOW);	/* Met les pins des leds en sortie */
	BUTTONS_DDR &= ~(BUTTON_1 | BUTTON_2); /* Met les pins des boutons en entrée (peut être enlevé) */
	BUTTONS_PORT |= (BUTTON_1 | BUTTON_2); /* Active les pull-up resistors pour les boutons */
}

/* Retourne l'état des Boutons ( 0, 1 ,2, 3) */
uint8_t Buttons_Get_State(void){
	
	uint8_t state = ~BUTTONS_PORT_IN & (BUTTON_1 | BUTTON_2); /* Lecture du port avec masque */
	
	state >>= PA1;	/* Right bit shift pour ramener les bits au LSB et obtenir les états 0,1,2,3 */
	
	return state;
}

/* Définis l'état des LEDs ( 0, 1 ,2, 3) */
void LEDs_Set_State(uint8_t state){
	
	state &= 0b00000011; /* Safeguard to allow only state 0, 1, 2 or 3*/
	
	state <<= PD2; /* Left shift pour amener la valeur d'état vis-à-vis les broches des LEDs */
	
	uint8_t LEDs_Port_State_Temp = LEDS_PORT;
	
	LEDs_Port_State_Temp &= ~(LED_BLUE | LED_YELLOW); /* Éteins les LEDs */
	
	LEDs_Port_State_Temp |= state;	/* Allume les LEDs selon l'état */
	
	LEDS_PORT = LEDs_Port_State_Temp;
}

/* Retourne l'état des LEDs ( 0, 1 ,2, 3) */
uint8_t LEDs_Get_State(void){
	
	uint8_t state = LEDS_PORT & (LED_BLUE | LED_YELLOW); /* Lecture du port avec masque */
	
	state >>= PD2; /* Right bit shift pour ramener les bits au LSB et avoir les états 0,1,2,3 */
	
	return state;
}


void Buttons_Watch_for_Event(volatile Button_Event_t* Button_Event){
	
	
	uint8_t Button_State = Buttons_Get_State();
	
	static uint8_t Pressed_Buttons = 0;
	
	Pressed_Buttons |= Button_State; /* Stores the buttons that have been pressed*/
	
	if (!Button_State){
		
		*Button_Event = (Button_Event_t)Pressed_Buttons;
		Pressed_Buttons = 0;
		
	}

}
