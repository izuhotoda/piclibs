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
#include <string.h>

void setup_rs232(void){
    /* Velocidad del puerto
     Estos elementos salen de la tabla 20-3 del datasheet del pic18f4550
     Se calculan en funcion de 
     la frecuencia del oscilador, (8.000.000)Hz
     la velocidad en baud (9600 bauds)
     8 Bits de datos, sin paridad y un bit de stop 
     buscando minimizar el error */

    /*===========================TO DO ===============================*/
    // colocar argumento para la velocidad tipo (N1,9600)

    BRGH = 1;
    BRG16 = 0;
    SPBRG = 51;
    
    SYNC = 0;       // Modo Asincronico
    SPEN = 1;       // EUSART Encendida
    
    // Configuracion para envio de bits
    TXCKP = 0;      // Inversion de niveles logicos off
    TXIE = 0;       // Interrupciones apagadas
    TX9 = 0;        // Noveno bit apagado
    TXEN = 1;       // Tx Activado
    
    // configuracion para recepcion 
    RXDTP = 0;       // inversion de niveles logicos
    RCIE = 0;       // interrupciones off
    RX9 = 0;        // 8bits
    CREN = 1;       // recepcion activate
    
    /* Cada vez que se cargue TXREG Se enviara el bit constantemente.
     * Luego espera un milisegundo entre cada uno supongo que 
     * depende del puerto de la computadora... Como sea con 1 us funciona bien
     */
    // Led de envio como salida
     TRISDbits.TRISD0 = 0;
     LATDbits.LATD0 = 0;   
}
////////////////////////////////////////////////////////////////////////////////

void send_rs232(char car){
    /* un caracter y lo envia por TX
     * con una espera de un 1ms para garantizar que paso en bit stop
    */
            LATDbits.LATD0 = 1;         // Luz de Tx
            TXREG = car;
            __delay_ms(1);
            LATDbits.LATD0 = 0;          
}
////////////////////////////////////////////////////////////////////////////////

void send_string_rs232(char *cad){
    /* recibe un string de caracteres (debe terminar con '\0')
     * Los envia por TX dejando 1ms de espacio entre cada caracter
     * Talvez podria funcionar con menos 
     * Al final de la cadena envia un caracter de nueva linea 0x00 = '\n'
    */ 
    /*===========================TO DO ===============================*/
    //Verificar '\0' en cad
    
    for(int i = 0; i < strlen(cad); i++)
        {
            LATDbits.LATD0 = 1;
            TXREG = cad[i];
            __delay_ms(1);
            LATDbits.LATD0 = 0;
        }
        TXREG = '\n';
        __delay_ms(1);
}
////////////////////////////////////////////////////////////////////////////////

char receive_rs232(void ){
    /* Espera indefinidamete la llegada de un caracter 
     * hace polling sobre el flag de interrupcion hasta que llega un byte
     * luego lo retorna
    */
    /*===========================TO DO ===============================*/
    // eliminar el delay de 1us
    LATDbits.LATD1 = 1;
    RCIF = 0;
    while(RCIF == 0)
    {        
        __delay_us(1);
    }
    RCIF = 0;
    
    LATDbits.LATD1 = 0;
    return RCREG;
}
////////////////////////////////////////////////////////////////////////////////


void receive_string_rs232(char *str_rec){
    /* recibe una cadena de caracteres por el puerto serie,
     * esperando indefinidamente
     * hasta que llega el 0x00
    */
    /*===========================TO DO ===============================*/
    // colocar un tamaño maximo para la entrada
    char r;
    int i = 0;
    do
	{
        r = receive_rs232();
        str_rec[i] = r;
        i++;
		
	} while (r == 0x00);
}
