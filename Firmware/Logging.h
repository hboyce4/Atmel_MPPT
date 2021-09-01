/*
 * Logging.h
 *
 * Created: 2019-10-14 15:13:07
 *  Author: Hugo Boyce
 */ 


#ifndef LOGGING_H_
#define LOGGING_H_

#include <avr/eeprom.h>
#include "Analog.h"
#include <stdbool.h>

#define EEPROM_ADRESS_PEAK_PV_P 4

typedef struct  {
	
	int16_t Peak_PV_P;
	bool New_Peak_PV_P;
	
} Logging_Data_t; /* Data that we are interested in logging*/
	
void Logging_Monitor_Values(volatile Analog_Data_t* Analog_Data, volatile Logging_Data_t* Logging_Data);
void Logging_Save_Log(volatile Logging_Data_t* Logging_Data);
void Logging_Fetch_Log(volatile Logging_Data_t* Logging_Data);

#endif /* LOGGING_H_ */