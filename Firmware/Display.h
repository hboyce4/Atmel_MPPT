/*
 * Display.h
 *
 * Created: 2019-02-25 15:33:25
 *  Author: Hugo Boyce
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdlib.h>
#include <stdint.h>
#include "SG12232A_Driver_1_0.h"
#include "Analog.h"
#include "System.h"

#define DECIMAL 10

#define BACKLIGHT_DDR	DDRD
#define BACKLIGHT_PIN	(1 << PD7)


void Display_Init(void);
void Display_Screen_Test(void);


void Display_P_I_V_Batt_PV(volatile Analog_Data_t* Analog_Data);
void Display_P_I_V_Conv_State(volatile Analog_Data_t* Analog_Data, int16_t Peak_PV_P, bool State, uint8_t Duty, Converter_User_Required_State_t User_Conv_State);
void Display_Battery_Type(uint8_t);

void Backlight_Init(void);
void Backlight_Set_Brightness(uint8_t);
uint8_t Backlight_Get_Brightness(void);



#endif /* DISPLAY_H_ */