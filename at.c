#include <xc.h>
#include <string.h>
#define _XTAL_FREQ 8000000
#include "rs232.h"
#include "at_datatype.h"
#include "at_commands.h"

//int removeChar(int c, char *str);

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
    
    string_at[i] = '\0';   // end of string '/0'
    
    // testing AT+
    if (string_at[0] == 'A' || string_at[0] == 'a')
        if(string_at[1] == 'T' || string_at[1] == 't')
            if (string_at[2] == '+')
                return 1;
    return 0;
}

/* function response_AT
 * characters string ended '\0'
 * arguments:
 *      str_res: respuesta del comado
 *       
 * envia la respuesta de un comando solicitado
 * TODO:
 * ---------------------------------------------------------------------------
 */
void response_AT(char *str_res){
    send_rs232('\x0c');
    send_rs232('\x0a');
    for(int i = 0; i < strlen(str_res); i++)
        send_rs232(str_res[i]);
    send_rs232('\x0c');
    send_rs232('\x0a');
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

/*
int removeChar(int c, char *str){
    if (c > strlen(str) - 1)
        return 0;
    else{
        for(int i = c; i < strlen(str)-1; i++)
            str[i] = str[i+1];
    }
    return 1;
}
 */ 
/////////////////// interface function //////////////////////////
/* Execute the command structure
 * return 0 if failed
 * 1 if exit */
int execute_AT(at_command *p_at_cmd){
	int i;
	for (i = 0; i < sizeof(cmd_list)/sizeof(cmd_list[0]); ++i){
		if (!(strcmp(p_at_cmd->cmd, cmd_list[i]))){
			return (*cmd_ptr[i])(p_at_cmd);
		}  
	}
    send_string_rs232("not implemented");
	return 0;
}