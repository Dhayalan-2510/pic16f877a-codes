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
#define BUTTON PORTBbits.RB0
#define LED PORTD

void main(void) {
    TRISD = 0x00;
    TRISB = 0x01;
    LED = 0x00;
    int count = 0;
    while(1)
    {
	    if (BUTTON == 0)
        {
            __delay_ms(300); // Debounce delay
            
            if(count > 8) 
                count = 0;  // To reset the count to because we have 8 LEDs
            
            switch(count)
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
            
            count += 1;
        }
    }
}