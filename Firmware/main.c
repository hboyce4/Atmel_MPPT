/*
 * MPPT_V0.9.7
 *
 * Created: 2020-08-25
 * Author : Hugo Boyce
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 20000000U
#endif
#include <util/delay.h>



#include "Buttons_and_LEDs.h"
#include "Analog.h"
#include "System.h"
#include "Display.h"
#include "Logging.h"



volatile ADC_Data_t ADC_Data = {0};	/* ADC data must be global and volatile. All initialized to zero */
volatile Analog_Data_t Current_Analog_Data = {0};
volatile Logging_Data_t Current_Logging_Data;
volatile Scan_Data_t Current_Scan_Data = {.Enable_Scan = true, .Scan_Countdown = SCAN_DIVIDER};
volatile Battery_Data_t Battery_Voltage_Limits = {0};

volatile Converter_User_Required_State_t Converter_User_Required_State;
volatile Button_Event_t Last_Button_Event = NO_BUTTON_PRESS;

int main(void)
{
	Timers_Init();
	Display_Init();
	Buttons_LEDs_Init();
	ADC_Init();
	Logging_Fetch_Log(&Current_Logging_Data);

	sei();	
	

	_delay_ms(10);
	uint8_t battery_type = Buttons_Get_State();
	Battery_Set_Limits(battery_type, &Battery_Voltage_Limits);
	Display_Battery_Type(battery_type);


	
    while (1) 
    {
		Logging_Save_Log(&Current_Logging_Data);
		
		Buttons_Watch_for_Event(&Last_Button_Event);
		
		Converter_Modify_State(&Last_Button_Event, &Converter_User_Required_State, &Current_Scan_Data);

		Display_P_I_V_Conv_State(&Current_Analog_Data, Current_Logging_Data.Peak_PV_P, Converter_Get_State(),OCR0B, Converter_User_Required_State);
		
		_delay_ms(10);
    }
}

ISR(TIMER2_OVF_vect, ISR_NOBLOCK){	/* Nested interrupts. Runs at 76.2939 Hz */
	
	ADC_Get_Analog_Data(&Current_Analog_Data, &Battery_Voltage_Limits); /* Refresh analog data*/	
	
	Logging_Monitor_Values(&Current_Analog_Data, &Current_Logging_Data);
	
	Converter_Main(&Converter_User_Required_State, &Current_Analog_Data, &Current_Scan_Data);
	
}