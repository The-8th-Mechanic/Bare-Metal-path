#include <Arduino.h>

void setup () {
DDRD |= (1<<PD2);

}

void loop () {
for (int brightness=0; brightness<=1000; brightness +=10) {
  PORTD |=(1<<PD2);
  delayMicroseconds(brightness);
  PORTD &= ~(1<<PD2);
  delayMicroseconds(1000-brightness);
}
 for (int brightness=1000;brightness>=0; brightness -= 10) {
PORTD |= (1<<PD2);
delayMicroseconds(brightness);
PORTD &= ~(1<<PD2);
delayMicroseconds(1000-brightness);


}


}