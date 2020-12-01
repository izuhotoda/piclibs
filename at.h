#ifndef AT_HEADER_H
#define AT_HEADER_H
#include "at_datatype.h"

/* listen at serial and catch the command saving en the argument
 * if parsing is correct AT+_______CR LF
 * then return 1
 * else return 0 */
int receive_AT(char* );

/* Parsing at_string to separate at command 
 * and mode
 * if parsing it's ok return 1
 * else return 0 */
int parsing_AT(char *at_string, at_command*);

/* Execute the command structure
 * return 0 if failed
 * 1 if exit */
int execute_AT(at_command*);

/* Send AT response
 * <CR><LF> whatever <CR><LF>
 */
void response_AT(char *str_res);

#endif