#include <Arduino.h>

void setup () {
DDRD = 0b11111100;
DDRB = 0b00000011;
Serial.begin(9600);


}

void loop () {
PORTB |= (1<<2);
Serial.print("This is using Serial.print");
Serial.println(PINB);

}
