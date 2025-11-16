
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set pin 8 (PB0) as output
    DDRB |= (1 << DDB0);

    while (1) {
        // Turn fan ON: set PB0 HIGH
        PORTB |= (1 << PORTB0);
        _delay_ms(3000); // 3 seconds ON

        // Turn fan OFF: set PB0 LOW
        PORTB &= ~(1 << PORTB0);
        _delay_ms(10000); // 10 seconds OFF
    }

    return 0; // never reached
}
