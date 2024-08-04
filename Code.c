#include <xc.h>

#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits
#pragma config WDTE = OFF            // Watchdog Timer Enable bit
#pragma config PWRTE = OFF           // Power-up Timer Enable bit
#pragma config MCLRE = ON            // RE3/MCLR pin function select bit
#pragma config CP = OFF              // Code Protection bit
#pragma config CPD = OFF             // Data Code Protection bit
#pragma config BOREN = OFF           // Brown-out Reset Enable bit
#pragma config IESO = OFF            // Internal/External Switchover bit
#pragma config FCMEN = OFF           // Fail-Safe Clock Monitor Enable bit
#pragma config LVP = OFF             // Low Voltage Programming Enable bit
#pragma config BOR4V = BOR40V        // Brown-out Reset Selection bit
#pragma config WRT = OFF             // Flash Program Memory Self Write Enable bits

#define _XTAL_FREQ 8000000           // 8 MHz clock frequency

// Function prototypes
void initSPI(void);
unsigned int readWeight(void);
void indicateWeightCorrectness(unsigned int weight);

void main(void) {
    unsigned int weight;

    // Initialize the SPI and peripherals
    initSPI();

    // Set ports for LED indicators
    TRISBbits.TRISB0 = 0; // Set RB0 as output (green LED)
    TRISBbits.TRISB1 = 0; // Set RB1 as output (red LED)
    PORTBbits.RB0 = 0;    // Turn off green LED
    PORTBbits.RB1 = 0;    // Turn off red LED

    // Main loop
    while (1) {
        // Read weight from the load cell
        weight = readWeight();

        // Indicate weight correctness
        indicateWeightCorrectness(weight);

        __delay_ms(1000); // Delay to allow process completion
    }
}

void initSPI(void) {
    // Configure SPI settings for MCP4921
    SSPSTAT = 0x40; // Sampling at middle
    SSPCON = 0x20;  // Enable SSP, FOSC/4, Master mode

    TRISC5 = 0; // SDO as output
    TRISC3 = 0; // SCK as output
    TRISC4 = 1; // SDI as input (if needed)
    TRISA5 = 0; // SS as output, manually controlled
}

unsigned int readWeight(void) {
    unsigned int weight = 0;

    // Simulate reading from HX710A (this would be hardware-specific)
    // Here, we'll just return a simulated weight value
    // Replace with actual code to read weight from the HX710A
    weight = 150; // Simulated weight in grams

    return weight;
}

void indicateWeightCorrectness(unsigned int weight) {
    if (weight >= 100 && weight <= 110) { // Assuming the correct weight range is 100-110 grams
        PORTBbits.RB0 = 1; // Turn on green LED
        PORTBbits.RB1 = 0; // Turn off red LED
    } else {
        PORTBbits.RB0 = 0; // Turn off green LED
        PORTBbits.RB1 = 1; // Turn on red LED
    }
}
