/*
 * System.h
 *
 * Created: 2018-05-27 18:15:01
 *  Author: hugo
 */ 


#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <avr/interrupt.h>
#include <stdbool.h>
#include "Analog.h"
#include "Buttons_and_LEDs.h"

#define CONVERTER_DDR DDRB
#define CONVERTER_OUT_PIN PB4
#define TIMER_0_TOP 100
#define BUTTON_PRESS_INCREMENT 1
#define DUTY_CYCLE_INITIAL_VALUE 5
#define MPPT_CHASE_DIVIDER 4 /* Max = 255. Value by which the analog refresh rate (76Hz) is divided to obtain the MPPT tracking or duty cycle refresh rate (19Hz) */ 
#define SCAN_DIVIDER 22800
#define PRE_SCAN_DELAY 5
#define POST_SCAN_DELAY 5

#define MIN_RUN_POWER 25 /* milliwatts */
#define OPEN_CIRCUIT_VOLTAGE_TURN_ON_THRESHOLD 21000 /* millivolts. In cold weather, 21000. Warm weather 20000. */


typedef struct {
	
	bool Enable_Scan;
	bool Scan_Tick;
	uint16_t Scan_Countdown;
	uint8_t PP_DutyCycle;
	uint16_t PP_Value;
	uint8_t Scan_Pre_Delay;
	uint8_t Scan_Post_Delay;
	
} Scan_Data_t; /*Struct that contains information relative to scanning the Duty Cycle vs Power curve */

typedef enum {OFF, ON, AUTO, SCAN} Converter_User_Required_State_t;
extern volatile Converter_User_Required_State_t Converter_User_Required_State;
extern volatile Battery_Data_t Battery_Voltage_Limits;

void Timers_Init(void);

void Converter_Main(volatile Converter_User_Required_State_t* Converter_User_Req, volatile Analog_Data_t* Analog_Data, volatile Scan_Data_t* Scan_Data);
void Converter_Update_Duty_Cycle(volatile Analog_Data_t* Analog_Data);
void Converter_Select_Run_State(volatile Analog_Data_t* Analog_Data, volatile Scan_Data_t* Scan_Data, bool* Run_State);
void Converter_Modify_State(volatile Button_Event_t* Button_Event, volatile Converter_User_Required_State_t* Converter_User_State, volatile Scan_Data_t* Scan_Data);
bool Converter_Scan_Next_Point(volatile Analog_Data_t* Analog_Data, volatile Scan_Data_t* Scan_Data);
void Converter_MPPT_Chase_Tick_Update(bool* MPPT_Chase_Tick);
void Converter_Scan_Tick_Update(volatile Scan_Data_t* Scan_Data);
void Converter_Enable(void);
void Converter_Disable(void);
bool Converter_Get_State(void);
void Converter_Start_Scan(volatile Scan_Data_t* Scan_Data, volatile Converter_User_Required_State_t* Conv_User_State);
void Converter_Start_Auto(volatile Scan_Data_t* Scan_Data, volatile Converter_User_Required_State_t* Conv_User_State);
void Battery_Set_Limits(uint8_t Battery_Type, volatile Battery_Data_t* Battery_Voltage_Limits);

#endif /* SYSTEM_H_ */