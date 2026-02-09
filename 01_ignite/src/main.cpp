#include <Arduino.h> /*
                       We need this library to use some arduino functions like delay etc.
                       We may get rid of it in the future.
                       */
#define LED_PIN PD2 
/*
look at your arduino datasheet for D2( i use connected the LED to pin D2 in wokwi), you will see it's also called PD2.
PD2 is the name of the name of the pin in the register, we use PD2 here like it's an integer, so that we can perform bitwise operations.
You will get it more as you see the code.

NOw,  i simple deside to create a variable( i meant a house) for PD2. so, i won't be calling PD2 but LED_PIN
Imaginge PD2 to be bit 2 represented by integer 2

*/

void setup() // VOID SETUP FUNCTION RUNS ONCE AND IT IS USE TO DEFINE PINS AND GIVE THEM VARIABLES OR SET THEM AS INPUT OR OUTPUT
{

  DDRD = (1<<LED_PIN); /*
   DDRD is the data direction register for port D, we use it to set pin as OUTPUT, by using bitwise logic. The (1<<LED_PIN) is a bitwise operation that shifts the number 1 to the left, by adding 2 zeros to the left of 1 , effectively setting the bit at that position to 1 and leaving all other bits unchanged.
   
   This is how it works:
   1 in arduino binary is 00000001 (NOTE THAT THE NUMBER OF DIGITS CAN NEVER BE GREATER THAN 8 BECAUSE WE ARE WORKING WITH 8 BITS)
   Also note that if you look at 00000001, the rightmost bit which is 1, has an index of 0. This means that from the rightmost bit to the leftmost bit, the total index is 7.
   so look at this particular 8 bit number 01001101, the index is like this (7,6,5,4,3,2,1,0) and the value of each bit is like this (0,1,0,0,1,1,0,1)

   Now we want to shift the 1 at the rightmost bit to 2 times to the left, that is we are trying to push that 1 into index 2, to make it 1 (if you read the README.md file, you will realise setting any DDRX pin to 1 is making it an OUTPUT).
   So, we pushed that 1 to the left using this operator "<<" and giving it the number of time we want to push it, which is 2 times( which is defined by LED_PIN AKA integer 2)
   so, 1 is pushed from index 0, to index 1, but "<<" is still angry and push 1 into index 2, where we want it to be.
   now, the 1 we are pushing left index 0, and move to index 1, and left index 1 to index 2. what we happen to index 0 and index 1?
   they will be filled automatically by zero.
   so now we have transformed 00000001 to 00000100(note the 2 zeros at the back, they just filled the spots "1" vacated)
   when we shift it to the left by 2 positions, it becomes 00000100, which is the binary representation of the number 4. This means that we are setting the bit at position 2 (which corresponds to pin D2) to 1, while all other bits remain unchanged.
  */
}

void loop() // this guy run over and over again
{
  PORTD |= (1<<LED_PIN);
  /*
  To understand here, u have to read the comment in the void setup function.
  so, if u read the comment at void setup, u will know what "(1<<LED_PIN)" does.
  
  PORTD IS simply the register we make a bit AKA pin HIGH or LOW.
  what we are tryng to do here si similar to what we did in void setup fucntion.
  we want to make index 2 ( which we set as OUTPUT in void setup) to be high USING bitwise logic

  here we use "|" operator, which is OR operator, to set the bit at position 2 to 1, while leaving all other bits unchanged. 
  The "|" operator compares each bit of the two operands and returns 1 if either of the bits is 1, otherwise it returns 0. So, when we apply the OR operator to PORTD and (1<<LED_PIN), it will set the bit at position 2 to 1, while leaving all other bits unchanged.
  let see some maths:
  0000    0000 (THIS IS PORTD CURRENT VALUE)
       OR          (Read about OR in logic gate)
  0000    0100 (THIS IS (1<<LED_PIN) VALUE)
  ------------
  0000    0100     (THIS IS THE RESULT OF PORTD | (1<<LED_PIN))

  */
  delay(1000); //delay means to do nothing for 1000 micro seconds or 1000 mili seconds(that is 1 seconds)
  PORTD &= ~(1<<LED_PIN);
  /*
  here we want to make index 2 (which was HIGH or 1) to be LOW or 0 using bitwise logic.
  so, we are using the bitwise AND operator "&" to set the bit at position 2 to 0, while leaving all other bits unchanged.
  the "~" operator is the bitwise NOT operator, which inverts all the bits in the expression. So, when we apply the NOT operator to (1<<LED_PIN), it will invert all the bits, turning the bit at position 2 to 0 and all other bits to 1.

   let see some maths:
  0000    0100 (THIS IS PORTD CURRENT VALUE)
       AND          (Read about AND in logic gate)
  1111    1011 (THIS IS ~(1<<LED_PIN) VALUE)     IT IS WAS GOTTEN BY INVERTING (1<<LED_PIN ) VALUE WHICH IS 0000 0100, SO THE 1 AT INDEX 2 BECAME 0, AND ALL OTHER BITS BECAME 1 (1111 1011)
  ------------
  0000    0000     (THIS IS THE RESULT OF PORTD & ~(1<<LED_PIN))

  */
  delay(1000);// DELAY MEANS TO DO NOTHING FOR 1000 MICRO SECONDS (THAT IS 1 SECONDS)


}