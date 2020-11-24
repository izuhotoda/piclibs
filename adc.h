/*
 * Captura la entrada del micro:
 * RA0/AN0 (pin 2)
 */
////////////////////////////////////////////////////////////////////////////////
#ifndef ADC_HEADER
#define ADC_HEADER
void adc_configure(void);
int adc_start(void);
#endif
