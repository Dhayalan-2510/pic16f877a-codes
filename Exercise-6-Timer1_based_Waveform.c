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

int count = 0;

void __interrupt() ISR(void)
{
    if (PIR1bits.TMR1IF)  // Timer1 overflow flag
    {
        count++;
        PIR1bits.TMR1IF = 0; // Clear overflow flag

        // 12 overflows ? 500ms
        if (count >= 12)
        {
            PROBE = ~PROBE;  // Toggle pin
            LED = ~LED; 
            count = 0;
        }

        // Reload Timer1 for accurate timing (65536 - 62492 = 3044)
        TMR1H = (62492 >> 8) & 0xFF;
        TMR1L = 62492 & 0xFF;
    }
}

void main(void) {
    // I/O setup
    TRISD = 0x00;
    PORTD = 0x00;

    // Timer1 setup
    T1CON = 0b00110001;  // Prescaler 1:4, Timer1 ON
    TMR1H = (62492 >> 8) & 0xFF;  // Preload high byte
    TMR1L = 62492 & 0xFF;         // Preload low byte

    // Interrupt setup
    PIE1bits.TMR1IE = 1;  // Enable Timer1 interrupt
    INTCONbits.PEIE = 1;  // Peripheral interrupts
    INTCONbits.GIE = 1;   // Global interrupts

    while(1){
        
    }
}