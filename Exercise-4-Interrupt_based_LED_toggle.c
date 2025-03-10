/*
 * File:   newmain.c
 * Author: Dhayalan R
 *
 * Created on 3 March, 2025, 11:44 PM
 */

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000
#define LED PORTDbits.RD0

void __interrupt() ISR(void)
{
    if (INTCONbits.INTF == 1)  // External Interrupt on RB0
    {
        LED = ~LED;
        INTCONbits.INTF = 0;  // Clear External Interrupt Flag
    }
}

void main(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.INTE = 1;
    
    OPTION_REGbits.INTEDG = 1;
    
    TRISD = 0x00;
    PORTD = 0x00;
    
    while(1){
        
    }
}