#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    // 1. Set PB5 (Pin 13) as output
    DDRB |= (1 << DDB5);   // Set bit 5 of DDRB to 1 (output)

    while (1)
    {
        // 2. Turn LED ON
        PORTB |= (1 << PORTB5);  // Set bit 5 (HIGH)
        _delay_ms(3000);         // Wait 3 seconds

        // 3. Turn LED OFF
        PORTB &= ~(1 << PORTB5); // Clear bit 5 (LOW)
        _delay_ms(1000);         // Wait 1 second
    }

    return 0;
}
