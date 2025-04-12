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
#define PROBE PORTDbits.RD0
#define LED PORTDbits.RD2
#define TIME_PERIOD 10

int count = TIME_PERIOD; //Each overflow 43 ms so 43*10 = 430ms

void __interrupt() ISR(void)
{
    if (INTCONbits.TMR0IF)  // External Interrupt on RB0
    {
        count--;
        INTCONbits.TMR0IF = 0;  // Clear External Interrupt Flag
        if(count == 0)
        {
            PROBE = ~PROBE;
            LED = ~LED;
            count = TIME_PERIOD;
        }
    }
}

void main(void) {
    TRISD = 0x00;
    PORTD = 0x00;
    
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    
    OPTION_REG = 0x07;
    TMR0 = 0;

    while(1){
        
    }
}
