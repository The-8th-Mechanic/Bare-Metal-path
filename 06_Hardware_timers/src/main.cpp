#include <Arduino.h>

void setup() {
 DDRD |= (1<<PD6); /*
 We set pin 6 to output using bitwsise logic. Pin 6 is connected to an LED.
 We are using pin 6 because it is connected to the output compare register A of timer 0.
  This means that we can use the hardware timer to control the LED without using the CPU. 
  This is more efficient and allows us to generate precise time intervals for the LED.

 */
 TCCR0A = 0; /*
 This is timer control register A. We set it to zero to clear any previous setting so as not to hamper our code.
 */
 TCCR0B = 0;
 /*
 We repated what we did to TCCR0A for TCCROB.
 */
 TCCR0A |= (1<<COM0A1) | (1<<WGM00) | (1<<WGM01);/*
 From the arduino datasheet, we can see that to set the timer to fast pwm mode, we need to set the WGM00 and WGM01 bits to 1.
 We also set the COM0A1 bit to 1 to enable the output compare match A mode. This means that it will count from 0 (the led turns on) to 127 (the value in OCR0A), then turns the led off, and keeps counting to 255 (the maximum value for an 8-bit timer), then it resets to 0 and starts counting again(turning the led on and repeating the same process again).
  This creates a PWM signal on pin 6, which controls the brightness of the LED.

 so remmeber that TCCR0A is for setting the wave generation mode and the compare output mode. We set it to fast pwm mode and enable the output compare match A mode.
 */
 TCCR0B |= (1<<CS00) | (1<<CS01);/*
 TCCR0B is for setting the clock source and the prescaler. 
 We set the CS00 and CS01 bits to 1 to set the clock source to the internal clock and the prescaler to 64. 
 This means that the timer will count at a rate of 16MHz/64 = 250kHz. 
 This allows us to generate precise time intervals for the LED.
 */
 OCR0A = 127;/*
 OCR0A is the output compare register A. we give it a value of 127 yo represent a duty cycle of 50%.
 note,that OCR0A is an8-bit register. It can counts from 0-255 (255 is 1111 1111 in binary).
  So to get a duty cycle of 50%, we need to set OCR0A to 127 (127 is 0111 1111 in binary). 
  This means that the LED will be on for 127 counts and off for 128 counts, resulting in a duty cycle of 50%.

  a duty cycle of 50% meant te led is on for 50% of the time and off for 50% of the time
  in thiscase,the led will be on for 127 counts and off for 128 counts.
  using a prescaler of 64 and a clock speed of 16MHz,the timer counts at a rate of 250KHz.
   This means that the LED will be on and off for 250 000/256 cycles per seconds (hz) . resulting in a total period of 0.0010235 seconds and a frequency of approximately 977Hz (this means the led is turning on and off 977 times per second)
 */
}

void loop() {

}