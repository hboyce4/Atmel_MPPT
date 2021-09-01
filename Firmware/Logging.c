/*
 * Logging.c
 *
 * Created: 2019-10-14 15:12:52
 *  Author: Hugo Boyce
 */ 

#include "Logging.h"

void Logging_Monitor_Values(volatile Analog_Data_t* Analog_Data, volatile Logging_Data_t* Logging_Data){
	
	if (Analog_Data->PV_P > Logging_Data->Peak_PV_P){
		
		Logging_Data->Peak_PV_P = Analog_Data->PV_P;
		Logging_Data->New_Peak_PV_P = true;
	}
	
}

void Logging_Save_Log(volatile Logging_Data_t* Logging_Data){
	
	if (Logging_Data->New_Peak_PV_P){
		
		eeprom_write_word((uint16_t*)EEPROM_ADRESS_PEAK_PV_P,(uint16_t)Logging_Data->Peak_PV_P);
		Logging_Data->New_Peak_PV_P = false;
	}
	
	
}

void Logging_Fetch_Log(volatile Logging_Data_t* Logging_Data){
	
	Logging_Data->Peak_PV_P = (int16_t)eeprom_read_word((uint16_t*)EEPROM_ADRESS_PEAK_PV_P);
	if(!(~Logging_Data->Peak_PV_P)) { /* If all bits = 1 (EEPROM is blank) */
		Logging_Data->Peak_PV_P = 0;
	}
}
