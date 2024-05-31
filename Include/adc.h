/*
 * adc.h
 *
 *  Created on: May 29, 2024
 *      Author: VOVAN
 */

#ifndef ADC_H_
#define ADC_H_
#include<stdint.h>
void pa1_adc_init(void);
uint32_t adc_read(void);
void star_conversion(void);

#endif /* ADC_H_ */
