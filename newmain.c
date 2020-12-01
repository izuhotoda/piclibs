   /*
 * File:   newmain.c
 * Author: arnet
 *
 * Created on June 4, 2020, 11:53 PM
 */

#include "config.h"
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "at.h"
#include "rs232.h"
#include "adc.h"
#define _XTAL_FREQ 8000000
#define N_LCTRS 10
#define MAX_AT_LENGTH 20

void main(void) {
    ////////////////// configuracion del microcontrolador //////////////////////
    OSCCON=0x70;
    setup_rs232();
    adc_configure();
        
    // Begin series
    
    send_string_rs232("Start"); // send
    
    char at_str[MAX_AT_LENGTH] = {0};              // received string
    at_command atcm = { "momo", AT_COMMAND_READ};
    at_command *p_at_cm = &atcm;
    
    while (1){        
        ///////////////////////////////////////////////////////////////
        if(receive_AT(at_str)){
            if(parsing_AT(at_str, p_at_cm)){
                if (execute_AT(p_at_cm)){
                    //send_string_rs232("execute success");                    
                }else
                    send_string_rs232("execute failed");
            }
            else
                send_string_rs232("parsing error");
        }else{
            send_string_rs232("Isn't an AT");
        }
        ///////////////////////////////////////////////////////////////
    } 
    return;
}
