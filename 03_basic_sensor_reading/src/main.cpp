#include <Arduino.h>

void setup () {
DDRD = 0b11111100; 
DDRB = 0b00000011;// note D10 AKA PB2 is 0. it's an INPUT pin
//Check project 2 (Sequneced_LED) to understand the above
Serial.begin(9600); // i am using serial monitor to print out values gotten from using PINx operator.
// Enable Pull-Up for Button on PB2
PORTB |= (1<<PB2);
/*
we enable pull_up resistor, by first of all making the pin we want to read it value, an input pin.
from the past projects, to make a pin an input, we simply set it DDRx register to 0.
THhis will make the pin to be used as an INPUT pin.
Then to enable pull-up resistor, we simply set the pin value (the Data register, that we use to turn on led etc) to high
note, that Data register is different from DDRx register( which is use to make a pin either OUTPUT or INPUT)

so, we simply made PORTB(Data Register B) equals to 1( setting it HIGH).
the reason for the pull-up resistor is to lock the pin at a value. setting the pin high means you are letting the full current (e,g 5v of an arduino) pin goe to that particular pin, and in this case PB2.
IF WE DO NOT make PB2 high, we will be getting erratic readings due to the fact that the pins will be picking up random voltages. The pins voltage will be floating.
So, we forcefully set it to HIGH(5V), so we will not have erratic reading, and we can use it to test if the value of the voltage is 0.

*/



}

void loop () {
Serial.print("PinB Value: ");
/*
we am simply trying to find the value of PINB before we press the pushbutton.
we are supposed to get a value of 4, which tells us that PB2 is high (check this particular project readme to see explanation)

*/
Serial.println(PINB); //REGISTER B VALUE GOTTEN BY USING PINB



int read_pin = PINB & (1<<PB2); 
/*
so, as we know, when ever we use PINx, we will get the value of the whole register.
the issue now fall on us to extract the value of the particular pin we want using bitwise logic

so here:
PINB (DATA REGISTER B) IS 4, which in binary is 0000 0100. 
This shows that,PB2 is high already. 
the goal, is to be able to detect changes in PB2
so, we created a temporary 8 bit binary, that is (1<<PB2)
(1<<PB2) is simply another way of saying 0000 0100. (check project 1 to understand this concept well)

so,we pperformed AND opeation on PINB and (1<<PB2), and the values are giving to read_pin variable.

when the pushbutton is not pressed, PINB is 4 (0000 0100)
so,when we perform AND on 0000 0100(PINB) and 0000 0100(1<<PB2)
we will get 0000 0100 (which is equals to 4)
mathemathically:
0000 0100  (PINB)
         x( AND is the same thing as multiply)
0000 0100  (1<<PB2)
---------
0000 0100   (RESULT = 4 IN DECIMAL)
---------

but when the pushbutton is pressed, PINB goes to 0.
this will be 0000 0000 (AKA 0 in decimal number).
if we try to perfrom AND on PINB and (1<<PB2)
we will eget 0, which will be saved to our read_pin variable
mathematically:
0000 0000  (PINB)
         x( AND is the same thing as multiply)
0000 0100 (1<<PB2)
---------
0000 0000   (RESULT = 0 IN DECIMAL)
---------

so, this code is to help us understand how to use baremetal to read and perform actions using  and reading a basic sensor (pushbutton)

*/
Serial.print("read_pin value: ");
Serial.println(read_pin); // use this to confirm read_pin value
Serial.println();

if (read_pin == 0) 
/*
So, we have an "IF" condition for when the pushbutton is pressed, the LEDS will light up
check project 2 for understanding how the LED WORKS
*/
{

for (int i=2;i<8;i++) {
    PORTD |= (1<<i);
    delay(80);
    PORTD &= ~(1<<i);
}
for (int i=0;i<2;i++) {
    PORTB |= (1<<i);
    delay(80);
    PORTB &= ~(1<<i);
}
}

}
