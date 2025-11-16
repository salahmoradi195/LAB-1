
/*
 * Bare-metal PWM fan speed ramp — Arduino Uno (ATmega328P)
 * Pin 9 → OC1A → transistor/MOSFET → 5 V fan
 */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL  // 16 MHz clock
#define FAN_PIN PB1        // OC1A = Pin 9

void pwm_init(void) {
    // Set OC1A (Pin 9) as output
    DDRB |= (1 << FAN_PIN);

    // Timer1 Fast PWM, 10-bit, non-inverting on OC1A
    // WGM13:0 = 0b0111 (Fast PWM 10-bit)
    // COM1A1:0 = 0b10 (non-inverting)
    TCCR1A = (1 << COM1A1) | (1 << WGM11) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11);  // prescaler = 8

    // Start with 0 % duty
    OCR1A = 0;
}

void set_pwm_duty(uint16_t duty) {
    // duty: 0–1023 (10-bit)
    if (duty > 1023) duty = 1023;
    OCR1A = duty;
}

int main(void) {
    pwm_init();

    while (1) {
        // Gradually increase fan speed over 5 seconds
        for (uint8_t i = 0; i <= 5; i++) {
            uint16_t duty = (i * 1023) / 5;  // 0 %, 20 %, 40 %, 60 %, 80 %, 100 %
            set_pwm_duty(duty);
            _delay_ms(1000);                 // wait 1 second
        }

        // Optional: keep max speed for a bit, then stop
        _delay_ms(5000);
        set_pwm_duty(0);
        _delay_ms(10000);
    }
}
