#include <xc.h>
#include <sys/attribs.h>


void initKeypad(){
    // RE1,3,5,7 outputs (rows)
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE3 = 0;
    TRISEbits.TRISE5 = 0;
    TRISEbits.TRISE7 = 0;
    
    // RE 0,2,4 inputs (columns)
    TRISEbits.TRISE0 = 1;
    TRISEbits.TRISE2 = 1;
    TRISEbits.TRISE4 = 1;
    
    // Enabling ODC mode for output pins
    ODCEbits.ODCE1 = 1;
    ODCEbits.ODCE3 = 1;
    ODCEbits.ODCE5 = 1;
    ODCEbits.ODCE7 = 1;
    
    // Input pins need pull-ups
    CNPUEbits.CNPUE0 = 1;
    CNPUEbits.CNPUE2 = 1;
    CNPUEbits.CNPUE4 = 1;
    
    // Now enable CN for each input pin
    CNCONEbits.ON = 1; //Enable overall CN Interrupt CNCONx
    CNENEbits.CNIEE0 = 1;//Enable pin CN CNENx
    CNENEbits.CNIEE2 = 1;//Enable pin CN CNENx
    CNENEbits.CNIEE4 = 1;//Enable pin CN CNENx
    IFS1bits.CNEIF = 0;//Put down the flag //IFSx
    IPC8bits.CNIP = 7;//Set an interrupt priority //IPCx
    IEC1bits.CNEIE = 1;//Enable interrupt for D pins
    
    // "Close" the ODC
    LATEbits.LATE1 = 1;
    LATEbits.LATE3 = 1;
    LATEbits.LATE5 = 1;
    LATEbits.LATE7 = 1;
}

int scanKeypad(){
    int key = -1;
    
    //Disable CN Interrupt
    IEC1bits.CNEIE = 0;
    
    // turn on only one row
    LATEbits.LATE1 = 1;
    LATEbits.LATE3 = 0;
    LATEbits.LATE5 = 0;
    LATEbits.LATE7 = 0;
    //delay
    if(PORTEbits.RE0 == 0) key = '1';
    else if(PORTEbits.RE2 == 0) key = '2';
    else if(PORTEbits.RE4 == 0) key = '3';
    
    //repeat scan

    
    // Return to keypad on
    LATEbits.LATE1 = 1;
    LATEbits.LATE3 = 1;
    LATEbits.LATE5 = 1;
    LATEbits.LATE7 = 1;
    
    // turn on the CN Interrupt
    IEC1bits.CNEIE = 1;
}