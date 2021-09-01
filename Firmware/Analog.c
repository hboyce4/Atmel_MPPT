/*
 * Analog.c
 *
 * Created: 2018-05-21 15:39:14
 *  Author: hugo
 */ 

#include "Analog.h"

void ADC_Init(void){
	
	/*PRR0 &= ~(1 << PRADC); Mise à zéro du bit Power Reduction ADC dans le Power Reduction Register. Pas nécessaire car initialisé à zéro. */
	
	DIDR0 = ((1 << ADC7D)|(1 << ADC6D)|(1 << ADC5D)|(1 << ADC4D));	/* Disabling the digital input buffers because they're not needed. */
	ADCSRA = ((1 << ADEN)|(1 << ADSC)|(1 << ADATE)|(1 << ADIE)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0));/* ADC Enable, ADC Start Conversion, ADC Auto trigger enable
																										ADC Interrupt Enable, Prescaler = 128, */
	ACSR = (1 << ACD); /* Set analog comparator disable bit to preserve power */
	
	ADMUX = (uint8_t)MUX_PV_V;
	ADC_Data.MuxHasChanged = true;
	
	
}

void ADC_Get_Analog_Data(volatile Analog_Data_t* Analog_Data, volatile Battery_Data_t* Battery_Limits){
	
	
	Analog_Data->PV_V = ADC_Data.Raw_PV_V * PV_V_GAIN; /* PV_V in millivolts*/
	Analog_Data->PV_I = (ADC_Data.Raw_PV_I - PV_I_OFFSET) * PV_I_GAIN; /* PV_I in tenths of milliamp */
	Analog_Data->Batt_V = ADC_Data.Raw_Batt_V * BATT_V_GAIN; /* Batt_V in millivolts*/	
	Analog_Data->Batt_I = (ADC_Data.Raw_Batt_I - BATT_I_OFFSET) * BATT_I_GAIN; /*Batt_I in milliamps*/

	Analog_Data->PV_P = (int16_t)(((int32_t)Analog_Data->PV_V * (int32_t)Analog_Data->PV_I)/10000); /* PV_P in milliwatts*/
	
	Analog_Data->Batt_P = (int16_t)(((int32_t)Analog_Data->Batt_V * (int32_t)Analog_Data->Batt_I)/1000); /* Batt_P in milliwatts*/
	
	if (Analog_Data->Batt_V > Battery_Limits->Batt_OV_Cut_In){ /* Update of battery overvoltage flag */
			
		Analog_Data->Batt_OV = true;
	}
	else if (Analog_Data->Batt_V < Battery_Limits->Batt_OV_Cut_Out){
			
		Analog_Data->Batt_OV = false;
	}
	
	if (Analog_Data->Batt_V < Battery_Limits->Batt_UV_Cut_In){ /* Update of battery undervoltage flag */
		
		Analog_Data->Batt_UV = true;
	}
	else if (Analog_Data->Batt_V > Battery_Limits->Batt_UV_Cut_Out){
		
		Analog_Data->Batt_UV = false;
	}
	
}



ISR(ADC_vect){
	
	/*LEDs_Set_State(LEDs_Get_State() ^ 0b00000010);*/
	
	//LEDs_Set_State(~(LEDs_Get_State()));
	
	if (ADC_Data.MuxHasChanged)			/* Si il s'agit de la première conversion après changement du multiplexeur*/
	{
		ADC_Data.MuxHasChanged = false;		/* On ne fait rien (on ignore la valeur obtenue). Et la prochaine conversion sera valide */
	} 
	else								/* Si il ne s'agit pas d'une première conversion */
	{
		switch ((ADC_Mux_Setting_t)ADMUX)	/* Selon l'état du MUX on accumule le résultat de la conversion dans la bonne variable */
		{
		case MUX_PV_V:
			ADC_Data.Raw_PV_V_Accu += ADC;
			ADC_Data.NumberOfSamples++;
			
			if (ADC_Data.NumberOfSamples >= AVG_N)	/* Si le nombre d'échantillons désiré est atteint*/
			{
				ADC_Data.Raw_PV_V_Accu >>= AVG_POWER;			/* Le résultat de l'accumulation est divisé par le nombre d'échantillons */
				ADC_Data.Raw_PV_V = ADC_Data.Raw_PV_V_Accu;	/*  Puis est transféré */				
				ADC_Data.Raw_PV_V_Accu = 0;					/* L'accumulateur est remis à zéro */
				ADC_Data.NumberOfSamples = 0;				/* Le compteur d'échantillons est remis à zéro */
				ADMUX = (uint8_t)MUX_PV_I;					/* Le multiplexeur est changé d'état pour le prochain canal */
				ADC_Data.MuxHasChanged = true;				/* L'indicateur de changement du multiplexeur est mis à "vrai" */
			}
			
			break;
			
		case MUX_PV_I:
			
			ADC_Data.Raw_PV_I_Accu += ADC;
			ADC_Data.NumberOfSamples++;
			
			if (ADC_Data.NumberOfSamples >= AVG_N)
			{
				
				ADC_Data.Raw_PV_I_Accu >>= AVG_POWER;
				ADC_Data.Raw_PV_I = ADC_Data.Raw_PV_I_Accu;
				ADC_Data.Raw_PV_I_Accu = 0;
				ADC_Data.NumberOfSamples = 0;
				ADMUX = (uint8_t)MUX_Batt_V;
				ADC_Data.MuxHasChanged = true;
			}
			
			
			break;
			
		case MUX_Batt_V:
			
			ADC_Data.Raw_Batt_V_Accu += ADC;
			ADC_Data.NumberOfSamples++;
			
			
			if (ADC_Data.NumberOfSamples >= AVG_N)
			{
				
				ADC_Data.Raw_Batt_V_Accu >>= AVG_POWER;
				ADC_Data.Raw_Batt_V = ADC_Data.Raw_Batt_V_Accu;
				ADC_Data.Raw_Batt_V_Accu = 0;
				ADC_Data.NumberOfSamples = 0;
				ADMUX = (uint8_t)MUX_Batt_I;
				ADC_Data.MuxHasChanged = true;
			}
			
			break;
			
		case MUX_Batt_I:
		
			ADC_Data.Raw_Batt_I_Accu += ADC;
			ADC_Data.NumberOfSamples++;
			
			
			if (ADC_Data.NumberOfSamples >= AVG_N)
			{
				
				ADC_Data.Raw_Batt_I_Accu >>= AVG_POWER;
				ADC_Data.Raw_Batt_I = ADC_Data.Raw_Batt_I_Accu;
				ADC_Data.Raw_Batt_I_Accu = 0;
				ADC_Data.NumberOfSamples = 0;
				ADMUX = (uint8_t)MUX_PV_V;			/* Après que les quatre canaux aient été fait, retour au premier canal. */
				ADC_Data.MuxHasChanged = true;
				
			}		
		
			break;
		}
	}
	
		//LEDs_Set_State(0);
}