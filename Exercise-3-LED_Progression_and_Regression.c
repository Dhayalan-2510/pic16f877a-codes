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
#define BUTTON_1 PORTBbits.RB0
#define BUTTON_2 PORTBbits.RB1
#define LED PORTD

void led_on(int *count)
{

    if(*count > 7) 
        *count = 0;
    else if (*count < 0)
        *count = 7;
    
    switch(*count)
        {
            case 0:
                LED = 0x01; break;
            case 1:
                LED = 0x03; break;
            case 2:
                LED = 0x07; break;
            case 3:
                LED = 0x0F; break;
            case 4:
                LED = 0x1F; break;
            case 5:
                LED = 0x3F; break;
            case 6:
                LED = 0x7F; break;
            case 7:
                LED = 0xFF; break;
            default:
                LED = 0x00;
        }
}

void main(void) {
    TRISD = 0x00;
    TRISB = 0x03;
    int count = 0;
    led_on(&count);
    
    while(1)
    {
	    if (BUTTON_1 == 0)
        {
            __delay_ms(300); // Debounce delay
            while(BUTTON_1 == 0);
            count += 1;
            led_on(&count);
        }
        else if (BUTTON_2 == 0)
        {
            __delay_ms(300); // Debounce delay
            while(BUTTON_2 == 0);
            count -= 1;
            led_on(&count);
        }
    }
}