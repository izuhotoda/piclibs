#ifndef AT_COMMANDS_HEADER_H
#define	AT_COMMANDS_HEADER_H

#include <stdio.h>
#include "at.h"
#include "adc.h"

/* Command definition:
 *      - se definen como funciones cuyo nombre es el nombre del comando
 *      - deben ser colocados en la lista de comandos
 *      - deben ser colocados en el array de funciones.
 * 
 * si se ejecuta correctamente 
 *      - response_AT("whatever")
 *      - response_AT("OK");
 *      - return 1;
 * si falla en la ejecucion
 *      -response_AT("whatever")
 *      - response_AT("ERROR");
 *      - return 0;
 * 
 int del(at_command *p_at_cm){
    switch (p_at_cm->mode){
        case AT_COMMAND_READ:
            response_AT("config parameters");
            break;
        case AT_COMMAND_RUN:
            response_AT("del running");
            break;
        case AT_COMMAND_TEST:
            // OK
            break;
        case AT_COMMAND_SET:
            response_AT("del setting");
            break;
    }
    response_AT("OK");
    return 1;    
}
 */
int t;
char tempStr[10] = {0};
int temp(at_command *p_at_cm){
    switch (p_at_cm->mode){
        case AT_COMMAND_TEST:
            // OK
            break;
        case AT_COMMAND_READ:
            response_AT("config parameters");
            break;
        case AT_COMMAND_RUN:
            t = adc_start();
            sprintf(tempStr, "%d", t);
            response_AT(tempStr);
            break;
        case AT_COMMAND_SET:
            response_AT("del setting");
            break;
    }
    response_AT("OK");
    return 1;    
}

int del(at_command *p_at_cm){
    switch (p_at_cm->mode){
        case AT_COMMAND_READ:
            response_AT("config parameters");
            break;
        case AT_COMMAND_RUN:
            response_AT("del running");
            break;
        case AT_COMMAND_TEST:
            // OK
            break;
        case AT_COMMAND_SET:
            response_AT("del setting");
            break;
    }
    response_AT("OK");
    return 1;    
}

int on(at_command *p_at_cm){
    switch (p_at_cm->mode){
        case AT_COMMAND_READ:
            response_AT("on read");
            break;
        case AT_COMMAND_RUN:
            response_AT("on running");
            break;
        case AT_COMMAND_TEST:
            // OK
            break;
        case AT_COMMAND_SET:
            response_AT("on setting");
            break;
    }
    response_AT("OK");
    return 1;    
}

int off(at_command *p_at_cm){
    switch (p_at_cm->mode){
        case AT_COMMAND_READ:
            response_AT("off read");
            break;
        case AT_COMMAND_RUN:
            response_AT("off running");
            break;
        case AT_COMMAND_TEST:
            // OK
            break;
        case AT_COMMAND_SET:
            response_AT("off setting");
            break;
    }
    response_AT("OK");
    return 1;    
}

//command index
int (*cmd_ptr[])() = {temp, del, on, off};              // pointer to function
const char *cmd_list[] = {"temp", "del", "on", "off"};     // key list
 

#endif