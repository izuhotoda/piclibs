/*
 * Este archivo contiene una serie de funciones que permite que el micricontro
 * lador pif18f4550 se comunique por el puerto serie.
 * Los parametor de configracaion son 9600 bauds con 8 bits de informacion
 * sin paridad y con un solo bit de parada 8N1:9600
 * 
 * No utiliza interrupcciones!!!
 * 25 TX
 * 26 RX
 * 19 LED
 */
////////////////////////////////////////////////////////////////////////////////
#ifndef RS232_HEADER
#define RS232_HEADER
void setup_rs232(void);
void send_rs232(char car);

void send_string_rs232(char *cad);
void send_raw_string_rs232(const char *cad);

char receive_rs232(void );
void receive_string_rs232(char *str_rec);

#endif