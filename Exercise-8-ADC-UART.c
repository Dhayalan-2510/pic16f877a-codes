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
#include <stdio.h>
#define _XTAL_FREQ 20000000

void ADC_init()
{
    ADCON1 = 0x80;
    TRISA = 0x01;
    ADCON0 = 0x41;
}

unsigned int ADC_Read()
{
   __delay_us(25);
   ADCON0bits.GO = 1;
   while(ADCON0bits.GO);
   return (unsigned int)((ADRESH << 8) + ADRESL);
}

void UART_init()
{
    TRISCbits.TRISC6 = 0; // TX pin
    TRISCbits.TRISC7 = 1; // RX pin
    
    SPBRG = 129; // Baud rate 9600 for 20MHz
    TXSTAbits.TXEN = 1; // Enable transmission
    TXSTAbits.BRGH = 1; // High baud rate
    TXSTAbits.SYNC = 0; // Asynchronous mode
    RCSTAbits.SPEN = 1; // Enable serial port
}

// Function to send a single character over UART
void UART_Write(char data) {
    while (!TXIF); // Wait until buffer is empty
    TXREG = data;
}

// Function to send a string
void UART_Write_Text(const char *text) {
    while (*text)
        UART_Write(*text++);
}

// Convert integer to string and send
void UART_Write_Number(unsigned int value) {
    char buffer[6]; // Max 5 digits + null terminator
    sprintf(buffer, "%u", value);
    UART_Write_Text(buffer);
}

void main(void)
{
    ADC_init();
    UART_init();
    
    while(1)
    {
        unsigned int adc_value = ADC_Read();
        UART_Write_Text("ADC: ");
        UART_Write_Number(adc_value);
        UART_Write(13);
        UART_Write(10);
        __delay_ms(500);
    }
}
