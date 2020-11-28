#ifndef AT_COMMANDS_HEADER_H
#define	AT_COMMANDS_HEADER_H

#include "at_datatype.h"

// command definition
int delete(at_command *p_at_cm){
    send_string_rs232("COMMAND: delete");
    /*
    send_string_rs232("COMMAND: delete");
    send_string_rs232(p_at_cm->cmd);
    switch (p_at_cm->mode){
    case AT_COMMAND_READ:
        // read implementation
        send_string_rs232("read");            
        break;
    case AT_COMMAND_RUN:
        // run implementation
        send_string_rs232("run");
        break;
    case AT_COMMAND_TEST:
        // test implementation
        send_string_rs232("test");
        break;
    case AT_COMMAND_SET:
        // set implementation
        send_string_rs232("set");
        break;
    }
     */ 
    return 1;
    
}
int on(at_command *p_at_cm){    
    send_string_rs232("COMMAND: on");
    return 1;
//	printf("on(%1d)\n", n);
}
int off(at_command *p_at_cm){
    
    send_string_rs232("COMMAND: off");
    return 1;
//	printf("off(%1d)\n", n);
}

//command index
int (*cmd_ptr[])() = {delete, on, off};              // pointer to function
const char *cmd_list[] = {"delete", "on", "off"};     // key list
 

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
#endif
