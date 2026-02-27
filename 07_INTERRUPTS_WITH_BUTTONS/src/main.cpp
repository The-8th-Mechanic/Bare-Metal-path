#include <avr/io.h>
#include <avr/interrupt.h>

volatile int brightness = 10;

void setup() {
DDRB |= (1<<PB5); // Set built-in LED as output

DDRD |= (1<<PD6);

DDRD &= ~((1<<PD2) | (1<<PD3));
PORTD |= (1<<PD2) | (1<<PD3);

EICRA |= (1<<ISC01) | (1<<ISC11);
EIMSK |= (1<<INT0) | (1<<INT1);

TCCR0A = 0;
TCCR0B = 0;

TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);
TCCR0B |= (1<<CS00) | (1<<CS01);

OCR0A = brightness;

sei();

}

ISR(INT0_vect) {
  PORTB ^= (1<<PB5); // Toggle Pin 13 every time the button is pressed
  brightness += 50;
  if (brightness >= 255) {
    brightness = 255;
  }
  // Reconnect the Timer to Pin 6!
  TCCR0A |= (1<<COM0A1);
  OCR0A = brightness;
}

ISR(INT1_vect) {
  PORTB ^= (1<<PB5); // Toggle Pin 13 every time the button is pressed
  brightness -= 50;
  if (brightness <= 0) {
    brightness = 0;
    TCCR0A &= ~(1<<COM0A1); 
    // Force the physical pin to absolute 0V
    PORTD &= ~(1<<PD6);
  }
  OCR0A = brightness;
}
void loop() {


}

int main(void) {
  setup();
  while (1) {
    loop(); // The CPU will spin here forever, doing nothing, waiting for the Interrupts.
  }
  return 0;
}