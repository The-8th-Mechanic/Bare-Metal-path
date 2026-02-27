#include <avr/io.h>
#include <avr/interrupt.h>
/*
The above files are AVR-specific header files that provide definitions for input/output operations and interrupt handling. 
They are necessary for working with AVR microcontrollers, such as those used in Arduino boards.
*/

volatile int brightness = 10; //set global variable  (brightness) to control LED brightness. It uses volatile to ensure compiler that not optimizes it away.

void setup() {
DDRB |= (1<<PB5); // Set built-in LED as output

DDRD |= (1<<PD6);// set pin 6 (LED pin) as output

DDRD &= ~((1<<PD2) | (1<<PD3)); // set pin 2 and 3 (buttons pin) to input.
PORTD |= (1<<PD2) | (1<<PD3);//enable pull-up resistor for pin 2 and 3

EICRA |= (1<<ISC01) | (1<<ISC11);
/*
The ECIRA register is used to configure which modes of external intterupts will trigger.
in this case, we set ISC01 and ISC11 to 1, which means that the interrupts will be triggered on the falling edge of the signal (when either button is pressed).
this means we want the same mode(falling edge. this means when the pins goes from high to zero/low) for the 2 buttons pins.
*/
EIMSK |= (1<<INT0) | (1<<INT1);
/*
EIMSK register is used to enable the external interrupts.
 By setting INT0 and INT1 bits to 1, we enable the interrupts for pin 2 and pin 3, respectively. 
 This allows the microcontroller to respond to button presses on those pins.
*/

TCCR0A = 0;//Clear TCCR0A register for future use
TCCR0B = 0;//Clear TCCR0B register for future use

TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);
/*
Set TCCR0A register to configure Timer0 for Fast PWM mode and to clear the output on compare match (non-inverting mode).
- COM0A1: This bit is set to 1 to enable the non-inverting mode for the output compare pin (Pin 6). This means that the output will be cleared on compare match, which is necessary for PWM control of brightness.
check project 6 to understnd timers
*/
TCCR0B |= (1<<CS00) | (1<<CS01);// To select a prescaler of 64 for Timer0

OCR0A = brightness; //equating OCR0A to brightness global variable.

sei();//Enable gloal interrupts

}

ISR(INT0_vect)// interrupt service routine for INT0 (Pin 2) - Increase brightness
{
  PORTB ^= (1<<PB5); // Toggle Pin 13 every time the button is pressed using xor logic
  brightness += 50;//increment brightness by 50 every time button is pressed
  if (brightness >= 255) {
    brightness = 255; 
    /*
    The if function exists to cap max brightness at 255, which is the register max value
    */
  }
  // Reconnect the Timer to Pin 6!
  TCCR0A |= (1<<COM0A1);// reconnect the timer to pin 6 by setting COM0A1 bit to 1 again, in case it was disconnected when brightness reached 0.
  OCR0A = brightness;//equate OCR0A to brightness to update the PWM duty cycle
}

ISR(INT1_vect)//interrupt servic routine for INT1(pin 3). decreases LED
 {
  PORTB ^= (1<<PB5); // Toggle Pin 13 every time the button is pressed
  brightness -= 50;//decremental counter
  if (brightness <= 0) {
    brightness = 0;//caps brithness min value to 0
    TCCR0A &= ~(1<<COM0A1); // disconnect the timer from pin 6 by clearing COM0A1 bit,which helps us to totally turns off the LED when brightness is 0,as opposed to just setting the duty cycle to 0, which may still allow a very faint glow.
    // Force the physical pin to absolute 0V
    PORTD &= ~(1<<PD6);//turns off led
  }
  OCR0A = brightness;//update the pwm duty cycle by equating OCR0A to brightness.
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