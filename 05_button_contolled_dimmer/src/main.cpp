#include <Arduino.h>

int brightness=0;
/*
This is the variable that stores the brightness of the LED.
it remembers the led last state, even when we are not pressing the  button.
*/

void setup() {

DDRD |= (1<<PD2); //set pin 2 to output,while p[in 4,and 5 are inputs
PORTD |= (1<<PD4) | (1<<PD5);//Enable pull-up resistor for pin 4 and 5

}

void loop() {
 
int PD4_value=PIND & (1<<PD4);
/*
Read the value of pin 4,using bitwise logic.
check project 2 on button sensor, to understand the operation

PIN 4 IS THE PIN CONNECTING THE RED BUTTON, WHICH INCREASES THE LED BRGHTNESS
*/
int PD5_value=PIND & (1<<PD5);
/*
Read pin 5 value using bitwise logic

PIN 5 IS THE PIN CONNECTING THE GREEN BUTTON, WHICH DECREASES THE LED BRGHTNESS
*/

if (PD4_value==0)//If the red button is pressed, the value of pin 4 will be 0, because we have enabled the pull-up resistor, which means that when the button is not pressed, the value will be 1, and when it is pressed, it will be 0.
{
  brightness+=2;//Increase the brightness by 2, every time we press the red button
  if (brightness>1000) //If the brightness exceeds 1000, we set it back to 1000, because the maximum value for the brightness is 1000, which corresponds to a duty cycle of 100%
{
 brightness=1000;//set brightness to 1000
}

}

else if (PD5_value==0)//if the green button is pressed, the inverse logic for the red button happens
{
brightness-=2;//brigntnes decrease
if (brightness<0)//if brightness less than 0, set it to 0 as the minimun value
{
  brightness=0;
 
}

}

PORTD |= (1<<PD2);//turn led on
delayMicroseconds(brightness);//delay for britghness duration
PORTD &= ~(1<<PD2);//turn led off
delayMicroseconds(1000-brightness);
//to understand this,check project 4

}

