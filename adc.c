#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc_types.h"


#define adcfunc 1
#define adcport 0
#define adcpin1 23 // mbed out pin is 15
#define adcpin2 24

void adc_init(void);

int adc_is_busy(int channel);

void adc_init(void){
    PINSEL_CFG_Type PinCfg;
    pin_settings(PinCfg, adcfunc, 0, 0, adcport, adcpin1);
    pin_settings(PinCfg, adcfunc, 0, 0, adcport, adcpin2);
    ADC_Init((LPC_ADC_TypeDef *)LPC_ADC, 20);
    ADC_ChannelCmd((LPC_ADC_TypeDef *)LPC_ADC, 0, ENABLE);
    ADC_IntConfig((LPC_ADC_TypeDef *) LPC_ADC, ADC_ADINTEN0, SET);
}

int adc_is_busy(int channel){
    return ADC_ChannelGetStatus((LPC_ADC_TypeDef *)LPC_ADC, channel, 0);
}

int adc_get_data(int channel){
    return ADC_ChannelGetData((LPC_ADC_TypeDef *)LPC_ADC, channel);
}


