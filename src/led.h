/* 
 * File:   led.h
 * Author: Alex Brooks
 *
 * Created on September 11
 */

#ifndef LED_H
#define	LED_H
#define RUN_TRIS TRISGbits.TRISG12
#define STOP_TRIS TRISGbits.TRISG14

#define RUN_LED LATGbits.LATG12
#define STOP_LED LATGbits.LATG14

#define LATCH 0
#define PORT 1

#define ON 0
#define OFF 1

void initLEDs(); // configure state of I/O on LED pins.
void preSetLEDs(); //turn on the running LED, turn off the other
void toggleLEDs();


#endif	/* LED_H */

