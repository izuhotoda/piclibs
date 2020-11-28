#include <xc.h>
#include <string.h>
#define _XTAL_FREQ 8000000
#include "rs232.h"
#include "at.h"

int removeChar(int c, char *str);

int receive_AT(char *string_at){    
    /* Espera de forma indefinida cuando
     * recibe una cadena de caracteres por el puerto serie,
     * la parsea y coloca el nombre del comando en cmd
     * y el modo en mode de la struct
     * si el analisis fue exito devuelve 1
     * si hubo un error devuelve 0 
     * solo retorna despues de recibido 0x0D
     * o cuado alcanzo el valor maximo
    */
    /*===========================TO DO ===============================*/
    char pars_str[10] = {0};      // array for parsing
    char r = 0x00;              // primera interaccion
    int i = 0;                  // index 
    
    do{
        r = receive_rs232();
        //////////////////////////////////////////////////////
        send_rs232(r);/////////// ECHO//////////////////////
        ///////////////////////////////////////////////////////
        string_at[i] = r;
        if (i < 20)
            i++;
        else
            return 0;
	} while (r != 0x0A);
    
     string_at[i] = 0x00;   // end of string '/0'
     
     // removing "AT+" and testing
     strncpy(pars_str, string_at, 3);
        return (strcmp("AT+", pars_str));        
}

/* function parsing_AT
 * arguments:   
 *      at_string:  pointer to string ended in /0
 *      at_cmd: struct name, mode
 * 
 * TODO
 * Borrar break for return
 * make #define max value
 * delete response
 */
int parsing_AT(char *at_cmd, at_command *patcmd){    
    
    for (int i = 0; i < 20; i++)
        patcmd->cmd[i] = '\0';
    
    for (int sub_index = 3; sub_index < 10 ; sub_index++){
        if (at_cmd[sub_index] == '\0')
            return 0;
        
        if (at_cmd[sub_index] == '?'){
            if (at_cmd[sub_index + 1] == '\x0d'){
                patcmd->mode = AT_COMMAND_READ;
                break;
            }else
                return 0;
        }
        
        if (at_cmd[sub_index] == '='){
            if (at_cmd[sub_index + 1] == '?'){
                patcmd->mode = AT_COMMAND_TEST;
                break;
            }else if ((at_cmd[sub_index + 1] != '\x0d') ||(at_cmd[sub_index + 1] != '\0')){
                patcmd->mode = AT_COMMAND_SET;
                break;
            }else
                return 0;            
        }
        
        if (at_cmd[sub_index] == '\x0d'){
            if (at_cmd[sub_index + 1] == '\x0a'){
                patcmd->mode = AT_COMMAND_RUN;
                break;
            }else
                return 0;            
        }        
        patcmd->cmd[sub_index - 3] = at_cmd[sub_index];        
    }    
    return 1;
}
    
int execute_AT(at_command * patcm){
    send_string_rs232("parsing AT");
    send_string_rs232(patcm->cmd);
    
    switch (patcm->mode){
        case AT_COMMAND_READ:
            send_string_rs232("read");
            break;
        case AT_COMMAND_RUN:
            send_string_rs232("run");
            break;
        case AT_COMMAND_TEST:
            send_string_rs232("test");
            break;
        case AT_COMMAND_SET:
            send_string_rs232("set");
            break;
    }
    return 1;
    
}

void receive_AT_rs232(char *str_rec){
    /* recibe una cadena de caracteres por el puerto serie,
     * y la guarda en el vector argumento
     * espera de forma indefinida
     * solo retorna despues de 0x0D
    */
    /*===========================TO DO ===============================*/
    // colocar un tamaño maximo para la entrada
    char r = 0x00;
    int i = 0;
    do{
        r = receive_rs232();
        //////////////////////////////////////////////////////
        send_rs232(r);/////////// ECHO//////////////////////
        ///////////////////////////////////////////////////////
        str_rec[i] = r;
        i++;		
	} while (r != 0x0A);
    str_rec[i] = 0x00;
}

void send_AT_rs232(char *cad){
    /* recibe un string de caracteres (debe terminar con '\0')
     * Los envia por TX dejando 1ms de espacio entre cada caracter
     * Talvez podria funcionar con menos 
     * Al final de la cadena envia un caracter de nueva linea 0x00 = '\n'
     * eg.
     * char s[]="shibanan";
     * send_string_rs232(s);
    */ 
    /*===========================TO DO ===============================*/
    //Verificar '\0' en cad
    LATDbits.LATD0 = 1;
    TXREG = 0x0d;
    __delay_ms(1);
    TXREG = 0x0a;
    __delay_ms(1);
    LATDbits.LATD0 = 0;
    
    for(int i = 0; i < strlen(cad); i++)
        {
            LATDbits.LATD0 = 1;
            TXREG = cad[i];
            __delay_ms(1);
            LATDbits.LATD0 = 0;
        }
    LATDbits.LATD0 = 1;
    TXREG = 0x0d;
    __delay_ms(1);
    TXREG = 0x0a;
    __delay_ms(1);
    LATDbits.LATD0 = 0;
}

int removeChar(int c, char *str){
    if (c > strlen(str) - 1)
        return 0;
    else{
        for(int i = c; i < strlen(str)-1; i++)
            str[i] = str[i+1];
    }
    return 1;
}