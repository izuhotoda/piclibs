#ifndef AT_DATATYPE_HEADER_H
#define	AT_DATATYPE_HEADER_H

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


#endif	

