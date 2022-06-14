#include "serial.h"
#include "serial.c"
#include "adc.c"
#include "dac.c"
#include "math.h"
#include "singen.c"
#include "lcd_display.c"


#define adcfunc 1
#define adcport 0
#define adcpin1 23
#define adcpin2 24

//void ADCIntHandler(void);

int main(void){

    serial_init();
    adc_init();
    dac_init();
    double* y;
    int freq = 1;
    int sample = 160;
    int amp = 1;

    y = singen(freq,amp,1, sample);
    for (i = 0; i <= sample; i++){
        char out[32] = "";
        sprintf(out, "%f", y[i]);
        write_usb_serial_blocking(out, 8);
        write_usb_serial_blocking("\n\r", 2);
    }

    int i = 0;

    while(1){
        //task1();
        if (i == 25000){
            freq += 1;
            amp += 1;
            sample *= 2;
            y = singen(freq, amp, 1, sample);
            i = 0;
        }
        else{
            task2(sample, y);
            i++;
        }
    }
    return 0;
}

void task1(void){
    while (adc_is_busy(0)){
        continue;
    }
    uint16_t x;
    x = adc_get_data(0);
    char port[32] = "";
    sprintf(port, "%i", x);
    write_usb_serial_blocking(port, 32);
    write_usb_serial_blocking("\n\r", 2);
}


void task2(int sample, double* y){
    int i;
    for (i = 0; i< sample; i++){
                dac_out((100*y[i]));
    }
}

void ADC_IRQHandler(void){
    uint16_t x = adc_get_data(0);
    char port[4] = "";
    sprintf(port, "%i", x);
    write_usb_serial_blocking(port, 4);
    write_usb_serial_blocking("\n\r", 2);
}
