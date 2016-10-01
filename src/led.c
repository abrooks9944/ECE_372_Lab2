/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include <proc/p32mx470f512l.h>
#include "led.h"


void initLEDs(){    
    RUN_TRIS  = 0;
    STOP_TRIS = 0;     
    preSetLEDs(); //clear LEDS except for the RUN_LED.

}

void preSetLEDs(){ //turn on the running LED, turn off the other
    RUN_LED = ON;
    STOP_LED = OFF;
}


void toggleLEDs(){
    RUN_LED = (RUN_LED + 1) % 2; //1 -> 0, 0 -> 1
    STOP_LED = (STOP_LED + 1) % 2;
}
