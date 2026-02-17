#include <Arduino.h>

void setup () {
DDRD |= (1<<PD2); //Turn on the LED connected to D2(Pin 2).

}

void loop () {
for (int i=0;i<=1000;i+=2) {
  PORTD |= (1<<PD2);
  delayMicroseconds(i);
  PORTD &= ~(1<<PD2);
  delayMicroseconds(1000-i);
}

for (int i=1000;i>=0;i-=2) {
  PORTD |= (1<<PD2);
  delayMicroseconds(i);
  PORTD &= ~(1<<PD2);
  delayMicroseconds(1000-i);
}

delay(1000);


}