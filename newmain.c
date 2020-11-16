   /*
 * File:   newmain.c
 * Author: arnet
 *
 * Created on June 4, 2020, 11:53 PM
 */

#include "config.h"
#include <xc.h>
#include <stdio.h>
#include "rs232.h"
#include "adc.h"
#define _XTAL_FREQ 8000000
#define N_LCTRS 10

void main(void) {
    ////////////////// configuracion del microcontrolador //////////////////////
    OSCCON=0x70;
    setup_rs232();
    adc_configure();
    // vars
    unsigned int counter = 0;           // counter
    int temps[N_LCTRS]= {0};            // Ultimas temperaturas
    float mean;   
    char str[20];                      //
    char strV[10];
    
    while (1){
        // data adq
        counter++;
        temps[counter % N_LCTRS] = adc_start();
        
        // mean
        mean = 0;
        for (int i = 0; i < N_LCTRS; i++)
            mean += (float)temps[i];
        mean /= N_LCTRS;
        
        // trasfer function
        mean = mean * 34.6 / 1024;
        
        // formating
        sprintf(str,"%d: ", counter); // counter to string
        sprintf(strV,"%.2f\'C", mean );  // temp to formated string
        strcat(str,strV);       // str += strV
        
        // send
        send_string_rs232(str); // send
        
        // wait
        __delay_ms(200);   
    } 
    return;
}