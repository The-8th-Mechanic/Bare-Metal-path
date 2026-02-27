#include <Arduino.h>

void setup () {
DDRD |= (1<<PD2); //Set the pin of the LED connected to D2 to OUTPUT.

}

void loop () {
  //FADE IN. This means increasing the slap strength from 0-1000 or increasing led brightness
for (int i=0;i<=1000;i+=2) 
/*
we are still using slaps analogy aned with a bit of eye an brain explanation.
so int the int i, simply means the time the slap lasts on your face. the maximum time for the time is 1000.
and it, increases in step of 2. so it starts with 0, moves to 2,4,6,8,10... 1000.
the slap is represented by 5v current from the arduino to the Led. 
we send the slap through this code "PORTD=(1<<PD2);" this means we are sending 5v to PD2,which then moves to the LED
*/
{
  PORTD |= (1<<PD2);//we turn on the led at t=0 or we can say this is the 1st slap on the led face
  delayMicroseconds(i);// use microsecconds cos it is faster than our eyes processing.we want to blur the input signal into 1 entity
  /*
  in the above code, we are let the time of the slap start from 0. so, in the 1st instance, the slap is barely noticeable
  */
  PORTD &= ~(1<<PD2);//now we remove our hand from the face. this means we turns off the led
  delayMicroseconds(1000-i);
  /*
  the above code is the time we wait before the slap comes again. 
  look at this, u were slapped at t=0 and the hand stayed on your face for 0 secs, u barely feeled anything, 
  then, u waited for 1000 secs brfore the next slap comes.
  the next slap is at t=2 microsec. it is stronger than the 1st slap because, it stayed on your face for 2 microsecond
  and then we waited for 998 microsec before the next slap comes. 
  note that,the time between slapp is getting stronger,and the pain intensity is getting higher
  and since we are dealing in microsecs and your sensors deals in millisecs, u can't process them individually, UR BRAIN SIMply combines all slaps into a 1 co tinous entity.

  so, in ths particular snppet of code (i mean the whole fade in), 
  the pain intensity increases from 0 at time increases, in connection to this project is meant the led brightnerss is increasing
  take the skin at your eyes, the brain at your brain, the slap as light from the led, the duration the slap is on your face, as the time the led is on and vice versa for when the slap is not on your face.

  */
}
//FADE OUT. This means decreasing the slap strength from 1000 to 0. AKA decreasing led brightness
for (int i=1000;i>=0;i-=2) 
/*
so, our last code takes the time to 1000, now we are to continue from 1000 to 0 in increment of 2.
if u read the readme, u will undestand this part easily
time here start from 1000, and is decreasing, this means pain intensity is decreasing
*/
{
  PORTD |= (1<<PD2);//turn on led
  delayMicroseconds(i);//delay from the highest time to the lowest time. this means the slap is at is peak when the code runs
  PORTD &= ~(1<<PD2);//turn off the led
  delayMicroseconds(1000-i);//then implement decreasing time
}

delay(1000);// to show u separate events. we dont want to combine a single brightening and dimming operation into a continous operation


}