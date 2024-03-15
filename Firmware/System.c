/*
 * System.c
 *
 * Created: 2018-05-27 18:14:45
 *  Author: hugo
 */ 

#include "System.h"


void Timers_Init(void){
	
	
	/* Initialize Timer 1 at 2 kHz */
	/* Timer 1 is used for: LCD clock signal */
	TCCR1A |= (1 << COM1B1 | (1 << WGM11));	/* Fast PWM, Clear on compare match (non inverting mode) */
	TCCR1B |= ((1 << CS10) | (1 << WGM13) | (1 << WGM12));		/* ClockI/O selected, Prescaler = 1, Fast PWM, TOP = ICR1 */
	ICR1 = 10000;				/* TOP = 10000; 20 MHz / 2kHz = 10000; */
	OCR1B = 5000;				/* 50% Duty Cycle -> 10000/2 = 5000 */
	
	
	/* Initialize Timer 2 at 76.2939 Hz */
	/* Timer 2 is used for: LCD backlight PWM */
	TCCR2A |= ((1 << COM2A1) | (1 << COM2A0) | (1 << WGM21) | (1 << WGM20));	/* Fast PWM, inverting mode because the LEDs are ON when the pin is LOW */
	TCCR2B |= ((1 << CS22)|(1 << CS21)|(1 << CS20));	/* Prescaler = 256, 20 MHz/(256 * 1024) = 76.2939 Hz */
	TIMSK2 |= (1 << TOIE2);	/* Timer overflow overflow interrupt enable */
	
	/* Initialize Timer 0 at 200 kHz */
	TCCR0A |= (1 << COM0B1 | (1 << WGM01) | (1 << WGM00));	/* Fast PWM, Clear on compare match (non-inverting) */
	TCCR0B |= ((1 << WGM02) | (1 << CS00) );		/* Prescaler = 1, TOP = OCR1A */
	OCR0A = TIMER_0_TOP;		/* 20 MHz / 200 kHz = 100; */
	OCR0B = TIMER_0_TOP/2; /* 50% duty cycle for starting */
	
	/* DDR bit must be set for the pin to output a square wave! */
	
}

void Converter_Main(volatile Converter_User_Required_State_t* Converter_User_Req, volatile Analog_Data_t* Analog_Data, volatile Scan_Data_t* Scan_Data){ /* Runs at 76.2939 Hz */
	
	static bool Converter_Run;

	if (*Converter_User_Req == ON || *Converter_User_Req == SCAN){ /* Determine the value of Converter_Run */
		
		Converter_Run = true;
	}
	else if (*Converter_User_Req == OFF){
		
		Converter_Run = false;
	}
	else if (*Converter_User_Req == AUTO){ /* If the user wants automatic operation*/
	
		if (Scan_Data->Scan_Post_Delay){
			
			Scan_Data->Scan_Post_Delay--;
			
		}else if (Converter_Get_State() && (Analog_Data->PV_P < MIN_RUN_POWER)){
				
			Converter_Run = false;
		}
			
		if (!Converter_Get_State() && (Analog_Data->PV_V > OPEN_CIRCUIT_VOLTAGE_TURN_ON_THRESHOLD)){
				
			Converter_Run = true;
			//Converter_Start_Scan(Scan_Data, Converter_User_Req);
		}
		
		Converter_Scan_Tick_Update(Scan_Data);
			
		if (Converter_Get_State()){ /* Si on est en mode Auto et que le convertisseur est actif*/
			
			if (Scan_Data->Scan_Tick && Scan_Data->Enable_Scan){
						
				Converter_Start_Scan(Scan_Data, Converter_User_Req);
			}
		}
			
	}


	static bool MPPT_Chase_Tick = 0;
	Converter_MPPT_Chase_Tick_Update(&MPPT_Chase_Tick);
		


	if (!Analog_Data->Batt_OV && Converter_Run){	/* If the battery is not in overvoltage and the converter can run*/
			
		Converter_Enable(); /* Turn on the converter*/
			
			
		if (MPPT_Chase_Tick){ /* If the counter has reached zero */
				MPPT_Chase_Tick = false;
				
				
			if (*Converter_User_Req == SCAN){/* If SCAN, do the scan, else do the MPPT chase/update duty cycle thing */
				
				if (Scan_Data->Scan_Pre_Delay){
					Scan_Data->Scan_Pre_Delay--;
					
				}else{
					if (!Converter_Scan_Next_Point(Analog_Data,Scan_Data)){/* La fct. Scan_Next_Point retourne vrai tant qu'il reste des points à scanner*/
						/*Donc, si il ne reste plus de points à scanner, on fait les choses suivantes:*/
						Converter_Start_Auto(Scan_Data, Converter_User_Req);
						
					}
				}
				
				/* Set mode back to AUTO after SCAN is finished */
				/* SCAN needs to be paced by MPPT_Chase_Tick */
			}else{
				Converter_Update_Duty_Cycle(Analog_Data); /* Update the converter */
			}
				
		}
			
			
	} else {
			
		Converter_Disable(); /* Turn off the converter */
			
	}

}


void Converter_Enable(void){
	
	CONVERTER_DDR |= (1 << CONVERTER_OUT_PIN); /* Set corresponding DDR bit */
	
}

void Converter_Disable(void){
	 
	 CONVERTER_DDR &= ~(1 << CONVERTER_OUT_PIN); /* Clear corresponding DDR bit */
	 
 }


bool Converter_Get_State(){
	
	uint8_t temp = CONVERTER_DDR;
	
	temp &= (1 << CONVERTER_OUT_PIN);
	
	return (bool)temp;
	
}


void Converter_Update_Duty_Cycle(volatile Analog_Data_t* Analog_Data){
	
	static int8_t Duty_Cycle_Increment = 1; /* Variable storing the direction of increment / decrement*/
	static int16_t Previous_PV_P; /* Stores the previous power figure to check if the duty cycle change has increased of decreased the power*/
	
	if (Analog_Data->PV_P < Previous_PV_P){ /* If the new power is lower than the previous power */
			
		Duty_Cycle_Increment *= -1;  /* change direction of increment*/
			
	}
		
	Previous_PV_P = Analog_Data->PV_P; /* Update the previous power for next time */
		
	/* special cases for upper and lower limits*/
		
	if (!(OCR0B)){ /* If OCR0B is equal to zero */
			
		Duty_Cycle_Increment = 1; /* Increment is set to one to move away from zero*/
	}
	else if (OCR0B >= (TIMER_0_TOP - 1)){ /* If OCR0B is at the maximum value */
			
		Duty_Cycle_Increment = -1; /* Increment is set to minus one to move away from the top */
	}	
		
	OCR0B += Duty_Cycle_Increment; /* Apply the increment (increase or decrease duty cycle) */
	
}



bool Converter_Scan_Next_Point(volatile Analog_Data_t* Analog_Data, volatile Scan_Data_t* Scan_Data){
	
	/* Fonction qui mémorise le duty cycle où la puissance est la plus élevée*/

	
	if (Analog_Data->PV_P > Scan_Data->PP_Value){
		
		Scan_Data->PP_Value = Analog_Data->PV_P;
		Scan_Data->PP_DutyCycle = OCR0B;
		
	}
	
	/*Retourne TRUE tant que le Duty cycle n'a pas atteint le max*/
	if (OCR0B < TIMER_0_TOP-1){
		OCR0B++;
		return true;
	}else{
		return false;
	}

}

void Converter_Modify_State(volatile Button_Event_t* Button_Event, volatile Converter_User_Required_State_t* Conv_User_State, volatile Scan_Data_t* Scan_Data){
	
	//static bool Button_Released_Flag;
	
	switch(*Button_Event) {
		
		case BUTTON_PRESS_1_AND_2: /* If event 0, toggle user required converter state*/
		if (*Conv_User_State == OFF){
			Converter_Start_Scan(Scan_Data, Conv_User_State);
		}
		else if (*Conv_User_State == SCAN){
			Converter_Start_Auto(Scan_Data, Conv_User_State);
		}
		else if (*Conv_User_State == AUTO){
			*Conv_User_State = ON;
		}
		else if (*Conv_User_State == ON){
			*Conv_User_State = OFF;
		}
		*Button_Event = NO_BUTTON_PRESS;
		break;
		
		case BUTTON_PRESS_2: /* If event 1, increment duty cycle */
		if (OCR0B < (TIMER_0_TOP-1)) /*If OCR0B hasn't reached the top yet*/
		{
			OCR0B += BUTTON_PRESS_INCREMENT;
		}
		*Button_Event = NO_BUTTON_PRESS;
		break;
		
		case BUTTON_PRESS_1: /* If event 2, decrement duty cycle */
		if (OCR0B) /* Si OCR0B non-zero */
		{
			OCR0B -= BUTTON_PRESS_INCREMENT;
		}
		*Button_Event = NO_BUTTON_PRESS;
		break;
		
		case NO_BUTTON_PRESS:
			/* Do nothing */
		break;
		
	}

}

void Converter_MPPT_Chase_Tick_Update(bool* MPPT_Chase_Tick){
	
	static uint8_t Update_Counter = MPPT_CHASE_DIVIDER;
	
	Update_Counter--; /* Decrement the divider counter */
	
	if (!Update_Counter){ /* If the counter has reached zero */
		*MPPT_Chase_Tick = true;
		Update_Counter = MPPT_CHASE_DIVIDER;
	}
	
}

void Converter_Scan_Tick_Update(volatile Scan_Data_t* Scan_Data){

	Scan_Data->Scan_Countdown--; /* Decrement the divider counter */
		
	if (!Scan_Data->Scan_Countdown){ /* If the counter has reached zero */
		Scan_Data->Scan_Tick = true;
		Scan_Data->Scan_Countdown = SCAN_DIVIDER;
	}
	
}

void Converter_Start_Scan(volatile Scan_Data_t* Scan_Data, volatile Converter_User_Required_State_t* Conv_User_State){
	
		*Conv_User_State = SCAN;
		Scan_Data->Scan_Tick = false;
		Scan_Data->PP_DutyCycle = 0;
		Scan_Data->PP_Value = 0;
		OCR0B = 0;
		Scan_Data->Scan_Pre_Delay = PRE_SCAN_DELAY;
		Scan_Data->Scan_Countdown = SCAN_DIVIDER;
	
}

void Converter_Start_Auto(volatile Scan_Data_t* Scan_Data, volatile Converter_User_Required_State_t* Conv_User_State){
	
	*Conv_User_State = AUTO;/* Retour au mode AUTO */
	OCR0B = Scan_Data->PP_DutyCycle; /* On met le convertisseur où la puissance est la plus élevée*/
	Scan_Data->Scan_Post_Delay = POST_SCAN_DELAY;
	
}
		
void Battery_Set_Limits(uint8_t Battery_Type, volatile Battery_Data_t* Battery_Voltage_Limits){
	
	if(Battery_Type == 3){ /*3S Lithium-Ion Mode*/
		
			Battery_Voltage_Limits->Batt_OV_Cut_In = 12000; // mV. Voltage above which battery is in overvoltage (charging should stop)
			Battery_Voltage_Limits->Batt_OV_Cut_Out = 11800; // mV. Voltage below which battery is out of overvoltage (charging can resume)
			Battery_Voltage_Limits->Batt_UV_Cut_In = 9000; // mV. Voltage below which battery is in undervoltage (discharge should stop)
			Battery_Voltage_Limits->Batt_UV_Cut_Out = 9450; // mV. Voltage above which battery is out of undervoltage (discharge can resume)
			
	}
	
	else if (Battery_Type == 2){ /*2S Lithium-Ion Mode*/
		
		Battery_Voltage_Limits->Batt_OV_Cut_In = 8000; // mV
		Battery_Voltage_Limits->Batt_OV_Cut_Out = 7900; // mV
		Battery_Voltage_Limits->Batt_UV_Cut_In = 6000; // mV
		Battery_Voltage_Limits->Batt_UV_Cut_Out = 6300; // mV
		
	}
	
	else if (Battery_Type ==1){ /* 12V Lead-Acid Mode */
		
		Battery_Voltage_Limits->Batt_OV_Cut_In = 13800; // mV
		Battery_Voltage_Limits->Batt_OV_Cut_Out = 13500; // mV
		Battery_Voltage_Limits->Batt_UV_Cut_In = 10800;	// mV
		Battery_Voltage_Limits->Batt_UV_Cut_Out = 11000; // mV
		
	}
	
	else {	/* 6V Lead-Acid Mode */
		
		Battery_Voltage_Limits->Batt_OV_Cut_In = 6900; // mV
		Battery_Voltage_Limits->Batt_OV_Cut_Out = 6800; // mV
		Battery_Voltage_Limits->Batt_UV_Cut_In = 5400;	// mV
		Battery_Voltage_Limits->Batt_UV_Cut_Out = 5500; // mV
		
		
	}
	
}
