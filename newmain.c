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
    // vars
    //unsigned int counter = 0;           // counter
    //int temps[N_LCTRS]= {0};            // Ultimas temperaturas
    //float mean;   
    char at_cmd[MAX_AT_LENGTH] = {0};              // received string
    char sub_at_cmd[10] = {0};      // array for parsing
    char sub_index = 0;
    
    // Begin series
    
    char init[]= "start";
    send_string_rs232(init); // send
    
    while (1){
        /*
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
        sprintf(strV,"%.2f\'C" , mean );  // temp to formated string
        find(str,strV);       // str += strV
        
        // send
        send_string_rs232(str); // send
        
        // wait
        __delay_ms(500);
        */
        at_command atcm = { "momo", AT_COMMAND_READ};
        ///////////////////////////////////////////////////////////////
        if(receive_AT(at_cmd)){
            send_raw_string_rs232(at_cmd);
            send_string_rs232("Itsn't a AT");
        }else{            
            send_raw_string_rs232(at_cmd);
            send_string_rs232(at_cmd);            
        }
        //////////////////////////////////////////////////////////////
        // parsing AT command
        
        
        /*
        receive_AT_rs232(at_cmd);
        strncpy(sub_at_cmd, at_cmd, 3);

        if (strcmp("AT+", sub_at_cmd))
            send_AT_rs232("ERROR");
        else
        {
            for (sub_index = 3; sub_index < MAX_AT_LENGTH ; sub_index++)
            {
                if (at_cmd[sub_index] == '\0'){
                    send_AT_rs232("END_ERROR");
                    break;
                }
          
                if (at_cmd[sub_index] == '?'){
                    if (at_cmd[sub_index + 1] == '\x0d'){
                        //send_AT_rs232(sub_at_cmd);
                        send_AT_rs232("READ");
                        break;
                    }else{
                        send_AT_rs232("READ_ERROR");
                        break;
                    }
                }
                if (at_cmd[sub_index] == '='){
                    if (at_cmd[sub_index + 1] == '?'){
                     //   send_AT_rs232(sub_at_cmd);
                        send_AT_rs232("TEST");
                           break;
                    }
                    else if ((at_cmd[sub_index + 1] != '\x0d') ||(at_cmd[sub_index + 1] != '\0')){
                        send_AT_rs232("SET");
                           break;
                    }else{
                        send_AT_rs232("EQUAL_ERROR");
                    }                                   
                }                               
                if (at_cmd[sub_index] == '\x0d'){
                    if (at_cmd[sub_index + 1] == '\x0a'){
                        //send_AT_rs232(sub_at_cmd);
                        send_AT_rs232("EXECUTE");
                           break;                        
                    }else{
                        send_AT_rs232("EXE_ERROR");
                           break;
                    }
                }                
            }
        }
        
         */
        
        
        
        /*       
        if (strcmp("AT\x0d\x0a", str))
            send_AT_rs232("ERROR");
        else
            send_AT_rs232("OK");
        
        */
        
        /*
        if (strcmp("AT", str))
            send_string_rs232("ok");
        else
            send_string_rs232("error");
        */ 
    } 
    return;
}