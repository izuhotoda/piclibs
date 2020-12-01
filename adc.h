/*
 * Captura la entrada del micro:
 * RA0/AN0 (pin 2)
 */
////////////////////////////////////////////////////////////////////////////////
#ifndef ADC_HEADER
#define ADC_HEADER
// configurar el puerto de entrada para AN0 que se comparte con RA0
void adc_configure(void);

// captura el valor del puerto de entrada (10 bits ) lo devuelve como un int(16bits)
int adc_start(void);

#endif
