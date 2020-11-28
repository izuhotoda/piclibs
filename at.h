#ifndef AT_HEADER
#define AT_HEADER

// commands type
enum at_command_mode {
	AT_COMMAND_READ,
	AT_COMMAND_TEST,
	AT_COMMAND_SET,
	AT_COMMAND_RUN
};

// basic structure for at command
typedef struct{
    char cmd[20];  // command name
    int mode;   // command type
}at_command;

/* listen at serial and catch the command saving en the argument
 * if parsing is correct AT+_______CR LF
 * then return 1
 * else return 0
 */
int receive_AT(char* );

/* Parsing at_string to separate at command 
 * and mode
 * if parsing it's ok return 1
 * else return 0
 */
int parsing_AT(char *at_string, at_command*);

/* Exexuteo the command structure
 * return 0 if failed
 * 1 if exit
 */
int execute_AT(at_command*);


// receive an AT COMMAND and  save on str_rec
void receive_AT_rs232(char *str_rec);

// send an AT RESPONCE
void send_AT_rs232(char *cad);

#endif