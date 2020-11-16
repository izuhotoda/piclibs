/*
 * Captura la entrada del micro:
 * RA0/AN0 (pin 2)
 */
////////////////////////////////////////////////////////////////////////////////
void adc_configure(void){
    /* configurar el puerto de entrada para AN0 que se comparte con RA0
     */
    /*===========================TO DO ===============================*/
    // implementar algunos parametros
 
    TRISAbits.RA0 = 1;
    /* configuaracion del ADC*/
    /* configurar los voltages de referencia 
     *  VSS y VDD---------- VCFG1:VCFG0 = 00
     * -AN2 y AN3 --------- VCFG1:VCFG0 = 11
     * 
     * ref: ADCON1 (Pag 268) */
    VCFG0 = 1;          // Vref+ --- 0:Vdd 1:AN3
    VCFG1 = 0;          // Vref- --- 0:Vss 1:AN2
    /*configurar canales de entradas como analogicos o digitales
     * para AN0 Como Analogica: PCFG3:PCFG0  = 1110
     * para AN0 como Digital:   PCFG3:PCFG0  = 1111
     *     
     * ref: ADCON1 (Pag 268) */
    PCFG3 = 1;
    PCFG2 = 1;
    PCFG1 = 1;
    PCFG0 = 0;
    /*Seleccinonar canales de entrada un solo canal por vez
     *  AN0 --------- CHS3:CHS0 = 0000
     *  ref: ADCON0 (Pag 267)*/
    CHS3 = 0;
    CHS2 = 0;
    CHS1 = 0;
    CHS0 = 0;
    /* configurar convert clock en funcion de frequencia del oscilador
     * Para cosas sencillas e mejor dejarlos con el oscilador interno que tiene
     * una frecuencia de 1MHz y el Tad = 2.45 us suficiente para cargar el
     * capacitor con error menor a LSB/2.
     * FRC: ----------------- ADCS2:ADCS0 = 011
     * ref: ADCON2 (Pag 271 y 267)*/
    ADCS2 = 0;
    ADCS1 = 1;
    ADCS0 = 1;
    /* configurar el tiempo de adquisicion necesatio para la carga del 
     * capacitor del ADC es necesario que sea mayor que 2,45 us para "cosas
     * normales", con 2 veces el Tad sera suficiente
     * 2 Tad: ----------------ACQT2:ACQT0 = 001
     * ref: ADCON2 ( 267)*/
    ACQT2 = 1;
    ACQT2 = 0;
    ACQT2 = 0;
    /* encender el Conversor AD*/
    ADON = 1;    
}
////////////////////////////////////////////////////////////////////////////////

int adc_start(void){
    /* captura el valor del puerto de entrada (10 bits ) lo devuelve como un
     entero de 16 bits*/
    GODONE = 1;
    while(GODONE == 1){   
    }    
    return ADRESH << 2 | ADRESL >> 6;
}