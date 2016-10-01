
/* 
 * File:   main.c
 * Author: Alex Brooks, Dallon Lines, Nathan Yokley
 * Description: lab 0 Part III.
 * Created on September 29, 2016
 */

#include <xc.h>
#include <sys/attribs.h>
#include <proc/p32mx470f512l.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"
#include "switch.h"
#include "lcd.h"
#include "keypad.h"

#define TRUE 1
#define FALSE 0

#define OUTPUT 0
#define INPUT 1


typedef enum stateEnum { //all states are for debouncing; states handle LEDs.
    updatePad,
    multiPress, 
    waitPress,
    waitRelease,
    debouncePress,
    debounceRelease     
} stateType;

volatile stateType state = waitPress;

int main(void) {
    SYSTEMConfigPerformance(10000000); //Important for stability
    enableInterrupts();
    initializeSwitches();
    initLCD();
    initKeypad();
    int keyPressed;
    int cursorRow = 0;
    int cursorColumn = 0;
    while (1) {
        switch (state) {

            case updatePad:
                if(cursorRow + 1 == 16)
                {
                    cursorColumn = (cursorColumn + 1) % 2;
                }
                cursorRow = (cursorRow + 1) % 16;
                moveCursorLCD(cursorRow, cursorColumn);
                writeToLCD(keyPressed);
                state = waitPress;
                break;
            case waitPress:
                break;
            case debouncePress:
                delayUs(5000); //debounce by .05 seconds
                state = waitRelease;
                break;
            case waitRelease:
                keyPressed = scanKeypad();
                break;
            case debounceRelease:
                delayUs(5000); //debounce by .05 seconds
                state = (keyPressed < 0) ? waitPress : updatePad;
                break;
        }

    }
}

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt(void) {
    IFS0bits.T1IF = 0; //lower the flag
}




void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt(void) {
    IFS1bits.CNAIF = 0;
    int x;
    x = PORTA; // clearing the mismatch condition
        
    if(state == waitRelease)
    {
        state = debounceRelease;
    }
    else if(state == waitPress)
    {
        
        state = debouncePress;
    }

} 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
