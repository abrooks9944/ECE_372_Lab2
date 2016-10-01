/* 
 * File:   timer.c
 * Author: Alex Brooks
 *
 */

#include <xc.h>
#include <math.h>
#include "lcd.h"
#define TRUE 1
#define FALSE 0



void delayUs(int usec) {
    TMR2 = 0;
    PR2 = calculatePR(usec); // .05 Seconds
    T2CONbits.TCKPS = 3; //prescalar of 8.
    T2CONbits.TCS = 0;
    T2CONbits.TON = 1; // Start the timer  
    IPC2bits.T2IP = 7; //assign the interrupt priority. 
    while (IFS0bits.T2IF == 0); // Do nothing until the flag goes up
    IFS0bits.T2IF = 0; // Put the flag back down
    T2CONbits.TON = 0; // Turn off the timer    
}

int calculatePR(int usec) {
    int PRTIME = 0;
    PRTIME = floor((float) (usec * 10)) / 8 - 1; //prescalar of 8.

    return PRTIME;
}







/* *****************************************************************************
 End of File
 */
