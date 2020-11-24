#include <xc.h>
#include <string.h>
#define _XTAL_FREQ 8000000
#include "rs232.h"
#include "at.h"


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

int parsing_AT(char *at_string, at_command *atcmd){
    
    return 0;
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