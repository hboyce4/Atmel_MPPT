/*
 * Analog.h
 *
 * Created: 2018-05-21 15:38:58
 *  Author: hugo
 */ 


#ifndef ANALOG_H_
#define ANALOG_H_

#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "Buttons_and_LEDs.h"

/*
Canaux utilisés:

ADC4: PV_V
ADC5: PV_I
ADC6: Batt_V
ADC7: Batt_I

Formules de conversion:

PV millivolts = ADC Count * 28
PV milliamp = ADC Count * 1
Battery millivolts = ADC Count * 16
Battery milliamps = (ADC Count - 260) * 4

*/

/* Gains and offsets for obtaining real voltages and currents*/
#define PV_V_GAIN 28
#define PV_I_GAIN 1
#define PV_I_OFFSET 9
#define BATT_V_GAIN 16
#define BATT_I_OFFSET 391
#define BATT_I_GAIN -5
#define SHIFT_FOR_AVG 16 /* Left shift a 16 bit value to 32 bits for AVG*/
#define FILTERING_CONSTANT 5415 /* Equal to (2^SHIFT_FOR_AVG)*T*w , where T is the sampling petiod (1/79Hz) and w is the cutoff req of the filter in rad/s (~6.2832 rad/s)  */


/* Values used for averaging */
#define AVG_POWER 3			/* Can be: 0, 1, 2, 3, 4, 5 or 6 */
#define AVG_N 8	/* 2 to the power of AVG_POWER. 1, 2, 4, 8, 16, 32 or 64 samples used for averaging. 64 samples max or else overflow. */
				/* For AVG_N = 8, Fsample for each channel = 333Hz */

typedef enum {
	
	MUX_PV_V = (1 << MUX2),
	MUX_PV_I = ((1 << MUX2)|(1 << MUX0)),
	MUX_Batt_V = ((1 << MUX2)|(1 << MUX1)),
	MUX_Batt_I = ((1 << MUX2)|(1 << MUX1)|(1 << MUX0)),
	
	} ADC_Mux_Setting_t;

typedef struct  {
	
	uint16_t Raw_PV_V;			/* Averaged, raw, 10-bit, right adjusted ADC values */
	uint16_t Raw_PV_I;
	uint16_t Raw_Batt_V;
	uint16_t Raw_Batt_I;
	
	/* Variables private to the interrupt */
	uint16_t Raw_PV_V_Accu;		/* Accumulator used for averaging */
	uint16_t Raw_PV_I_Accu;
	uint16_t Raw_Batt_V_Accu;
	uint16_t Raw_Batt_I_Accu;
	bool MuxHasChanged;			/* Flag to indicate if the current conversion is the first one after the MUX was changed. */
	uint8_t NumberOfSamples;	/* Counter of the number of samples for averaging. */
	
} ADC_Data_t;

typedef struct  {
	
	int16_t PV_V;		/* Solar panel voltage in mV */
	int16_t PV_I;		/* Solar panel current in 100s of uA (or tenths of mA)*/
	int16_t PV_P;		/* Solar panel power, in mW */
	int32_t PV_P_avg;	/* Solar panel average power, in mW, multiplied by 2^SHIFT_FOR_AVG */
	int16_t Batt_V;	/* Battery voltage, in mV */
	int16_t  Batt_I;	/* Battery current, in mA */
	int16_t  Batt_P;	/* Battery power, in mW */
	
	bool Batt_OV; /* Battery voltage is not okay for charging*/
	bool Batt_UV; /* Battery voltage is not okay for discharging*/
	
} Analog_Data_t;


typedef struct {
	
	int16_t Batt_OV_Cut_In;
	int16_t Batt_OV_Cut_Out;
	int16_t Batt_UV_Cut_In;
	int16_t Batt_UV_Cut_Out;

} Battery_Data_t; /* Struct that contains information about the safe voltage threshold for a battery */



extern volatile ADC_Data_t ADC_Data;
extern volatile Analog_Data_t Analog_Data;
extern volatile Battery_Data_t Battery_Voltage_Limits;

void ADC_Init(void);
void ADC_Get_Analog_Data(volatile Analog_Data_t*, volatile Battery_Data_t*);
void Analog_Calc_Avg(volatile Analog_Data_t*);


#endif /* ANALOG_H_ */