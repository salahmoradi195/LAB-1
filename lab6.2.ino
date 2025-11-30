#include <avr/io.h>
#include <util/delay.h>

void SPI_MasterInit(void) {
    // Set MOSI (PB3), SCK (PB5), SS (PB2) as output
    DDRB |= (1<<PB3) | (1<<PB5) | (1<<PB2);

    // SPI Control Register setup:
    // SPE  = 1 → Enable SPI
    // MSTR = 1 → Master mode
    // CPOL = 1 → Clock idle high
    // CPHA = 1 → Sample on falling edge
    // DORD = 0 → MSB first
    // SPR0 = 1, SPR1 = 0 → Fosc/16
    SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR0);

    // Ensure SPI2X = 0 → keeps speed = Fosc/16
    SPSR &= ~(1<<SPI2X);
}

void SPI_MasterTransmit(uint8_t data) {
    SPDR = data;                      // Load data to SPI Data Register
    while (!(SPSR & (1<<SPIF)));      // Wait until transmission complete
}

int main(void) {
    SPI_MasterInit();

    while (1) {
        SPI_MasterTransmit(0x55);     // Example byte to send
        _delay_ms(1000);
    }

    return 0;
}
