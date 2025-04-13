// CONFIG
#pragma config FOSC = EXTRC     // RC oscillator
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF      
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF         

#include <xc.h>
#define _XTAL_FREQ 20000000

#define LED PORTDbits.RD0
#define PROBE PORTCbits.RC2  // CCP1 output is on RC2

volatile uint8_t count = 0;
volatile uint16_t duty_cycle = 50;

void __interrupt() ISR(void)
{
    if(PIR1bits.TMR1IF)
    {
        PIR1bits.TMR1IF = 0;
        count++;
        
        if (count >= 10)
        {
            if(duty_cycle > 450)
                duty_cycle = 50;
            else
                duty_cycle += 50;

            // Update PWM duty cycle here
            CCPR1L = (unsigned char)(duty_cycle >> 2);
            CCP1CONbits.CCP1X = (duty_cycle & 0x02) >> 1;
            CCP1CONbits.CCP1Y = (duty_cycle & 0x01);

            count = 0;
            LED = ~LED;
        }

        // TIMER 1 PRELOAD
        TMR1H = (59286 >> 8) & 0xFF;
        TMR1L = 59286 & 0xFF;
    }
}

void main(void)
{
    // PIN Setup
    TRISD = 0x00;
    TRISCbits.TRISC2 = 0; // CCP1 as output
    LED = 0;
    
    // TIMER 1 DELAY SETUP
    INTCONbits.GIE = 1; // Global Interrupt Enable
    INTCONbits.PEIE = 1; // Peripheral Interrupt Enable
    PIE1bits.TMR1IE = 1; // Timer 1 interrupt
    T1CON = 0b00110001; // In binary -> 00110001
    
    // TIMER 1 PRELOAD
    TMR1H = (59286 >> 8) & 0xFF;
    TMR1L = 59286 & 0xFF;
    
    // PWM Settings
    T2CON = 0b00000100;
    PR2 = 124;
    CCP1CON = 0x0C;
    CCPR1L = (unsigned char)(duty_cycle >> 2);
    CCP1CONbits.CCP1X = (duty_cycle & 0x02) >> 1;
    CCP1CONbits.CCP1Y = (duty_cycle & 0x01);
    
    
    while (1)
    {
        // Main loop does nothing;
    }
}
