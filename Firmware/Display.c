/*
 * Display.c
 *
 * Created: 2019-02-25 15:33:07
 *  Author: Hugo Boyce
 */ 
#include "Display.h"


void Display_Init(void){
	
	glcd_init();
	glcd_fillScreen(0);
	
		//glcd_WriteString_P(PSTR("Test"));
	
	Backlight_Init();
	Backlight_Set_Brightness(0);
	
}

void Display_Screen_Test(void){
	
	
	static int8_t x, y;
	static int8_t dx =1, dy = 1;
	
	glcd_pixel(x, y,1);
	
	x += dx;
	y += dy;
	
	if (x >= SCREEN_WIDTH){
		dx = -1;
	} else if (!x){
		dx = 1;
	}
	
	if (y >= SCREEN_HEIGHT){
		dy = -1;
	} else if (!y){
		dy = 1;
	}
	
}


/*
void Display_P_I_V_Batt_PV(volatile Analog_Data_t* Analog_Data){
	
	char String_Buffer[8];
	
	GLCD_ClearScreen();
	
	GLCD_GoTo(0, 0);			
	itoa(Analog_Data->PV_V, String_Buffer, DECIMAL);
	glcd_WriteString(String_Buffer);
	
	GLCD_GoTo(64, 0);
	itoa(Analog_Data->PV_P, String_Buffer, DECIMAL);
	glcd_WriteString(String_Buffer);
			
	GLCD_GoTo(0, 1);
	itoa(Analog_Data->PV_I, String_Buffer, DECIMAL);
	glcd_WriteString(String_Buffer);	
			
	GLCD_GoTo(0, 2);
	itoa(Analog_Data->Batt_V, String_Buffer, DECIMAL);
	glcd_WriteString(String_Buffer);
	
	GLCD_GoTo(64, 2);
	itoa(Analog_Data->Batt_P, String_Buffer, DECIMAL);
	glcd_WriteString(String_Buffer);	
			
	GLCD_GoTo(0, 3);
	itoa(Analog_Data->Batt_I, String_Buffer, DECIMAL);
	glcd_WriteString(String_Buffer);
	
}*/


void Display_P_I_V_Conv_State(volatile Analog_Data_t* Analog_Data, int16_t Peak_PV_P, bool State, uint8_t Duty, Converter_User_Required_State_t User_Conv_State){
	
	
	char String_Buffer[8];
	uint8_t x_pos, y_pos;
	
	glcd_fillScreen(0);
	
	x_pos = 0;
	y_pos = 0;
	itoa(Analog_Data->PV_V, String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	
	x_pos = 64;
	itoa((int)((Analog_Data->PV_P_avg)>>SHIFT_FOR_AVG), String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	glcd_WriteString_P(&x_pos, &y_pos,PSTR("/"));
	itoa(Peak_PV_P, String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	
	x_pos = 0;
	y_pos = 1;
	itoa(Analog_Data->PV_I, String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	
	x_pos = 64;
	if (Converter_User_Required_State == ON){
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("ON/"));
	}
	else if (Converter_User_Required_State == OFF){
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("OFF/"));
	}
	else if (Converter_User_Required_State == AUTO){
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("AUTO/"));
	}
	else if (Converter_User_Required_State == SCAN){
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("SCAN/"));
	}
	
	if (State){
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("ON "));
	}
	else {
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("OFF"));
	}
	
	
	x_pos = 0;
	y_pos = 2;
	itoa(Analog_Data->Batt_V, String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	
	x_pos = 64;
	itoa(Analog_Data->Batt_P, String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	
	x_pos = 0;
	y_pos = 3;
	itoa(Analog_Data->Batt_I, String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	
	x_pos = 64;
	itoa(Duty, String_Buffer, DECIMAL);
	glcd_WriteString(&x_pos, &y_pos,String_Buffer);
	
}

void Display_Battery_Type(uint8_t type){
	
	uint8_t x_pos = 0;
	uint8_t y_pos = 0;
	
	if(type == 3){ /*3S Lithium-Ion Mode*/
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("3S Li-Ion 12.6V"));
	
	}
	
	else if (type == 2){ /*2S Lithium-Ion Mode*/
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("2S Li-Ion 8.4V"));
		
	}
	
	else if (type == 1){ /* 12V Lead-Acid Mode */
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("12V Lead-Acid"));
		
	}
	
	else {	/* 6V Lead-Acid Mode */
		glcd_WriteString_P(&x_pos, &y_pos,PSTR("6V Lead-Acid"));
			
	}
	
	x_pos = 0;
	y_pos = 1;
	glcd_WriteString_P(&x_pos, &y_pos,PSTR("battery selected."));
	
	
	_delay_ms(3000);
	
}
	



void Backlight_Init(void){

	/* !!!WARNING!!! This function does something only after Timer 2 has been initialized, i.e. Timer2_Init(); has been run. */
	
	BACKLIGHT_DDR |= BACKLIGHT_PIN;	/* Met la broche en mode sortie*/
	
}

void Backlight_Set_Brightness(uint8_t brightness){
	
	OCR2A = brightness;
}

uint8_t Backlight_Get_Brightness(void){
	
	return OCR2A;
}

