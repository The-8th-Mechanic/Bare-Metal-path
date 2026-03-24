#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>//THis is to allow us to use the delay function


void uart_init(unsigned int baud_calc) 
/*
This is the functions that initializes the serial monitor.

So arduino moves at 16mhz speed.And we want a baud rate of 9600 (that is u are sending 9600 bits a sec)
so, essentially, the there is a gap of free 1667 clock cycles before the next bit is sent.
i got 1667 by:
if 9600 bits is sent in 1 sec, and there is 16,000,000 cycle in 1 sec. 
then 9600 is equivalent to 16,000,000. therefore number of cycle for 1 bit = (16,000,000*1 sec)/9600 = 1666.7 aprox 1667 cycles.

so, because data/bits can be corrupted, we need to check for errors.
the arduino solves this by reading the same values 16 times instead of once.
then it goes to the middle and select the 3 middle values/numbers/strings
then it llok at the 3 values, and select the majority.
imagine, the srduino is to send a value of 80.
it reads it 16 times, and the extracted middle values are 80,0,80.
it will select 80,since it's the majority.

*/
{
  UBRR0L = baud_calc; /*
Now, we said we want the serial monitor to move at 9600 baud rate, but the arduino moves at 16mhz
we can't connect them together,therefore we need a special "prescaler" to bring it down

this prescaler has a gear ratio that is calculated. 
i decided to name the gear ratio "baud_calc". u can name it anything.
baud_calc is known as UBRR

the formula for baud_calc is  UBRR/baud_calc = (F(CPU)
                                            (----------------) - 1
                                              (16*BAUD)) 

WHERE Fcpu is the arduino clock speed 16mhz
"16" is the number of times the arduino checks the data
BAUD is the baud rate u want, in this case it's 9600.

so for 9600 baud rate, our  baud calc or UBRR is 104.
we used 103 instead of 104 cos it's better. u will figure that one out later

  UBRR0L (USART BAUD RATE REGISTER) is part of a 12bit register.
  we are using a 12bit register for cases where the baud_calc is above 255(this is for 8bit)
  so, we put the last 8bits into the lower register (UBRR0L).

  We do this by simply equating UBRR0L to the baud_calc value. 
  arduino will chop off, the upper part after it has put the last 8 bits into the register

  for this case 103 in binary is: 0110 0111
  so,since this is 8 bit, everythingis shoved into the lower register

  now let do for 506(baud_calc)
  506 is "1 1111 1010" in binary
  so we shove the last 8 "1111 1010" into UBRR0L
  and then then shove "1" into UBRR0H (the 1st "1")
  */
  UBRR0H = (baud_calc >> 8);/*
  Here we are shoving the upper part of the baud_calc into UBRR0H, by usign right shift operator.
  since,UBRR0L is an 8 bit register, it can only accept the last 8 digits of any baud_calc.
  The upper ones are then put into UBRR0H by right shifting the baud_calc 8 times.
  */

  UCSR0B |= (1 << TXEN0);/*
  If this bit is 0, the TX pin (Pin 1) acts like a normal digital pin.
   If you set it to 1, the UART hardware violently hijacks Pin 1, taking it away from the normal GPIO system, and connects it directly to the UART transmission line.
  */
  UCSR0C |= ((1 << UCSZ00) | (1 << UCSZ01));
  UCSR0B &= ~(1 << UCSZ02);
  /*
  The last 2 lines of code are to simply configure the size of the data we will be dealing with
  we want to deal with 8-bits data, we can simply check " UCSZn Bits Settings" table in the datasheet
  this gives us the specific configuration to select 8  bit
  */
}

void uart_transmit(unsigned char data)
/*
this is the function that we drops whatever we want to sent
*/
{
  while (!(UCSR0A & (1<<UDRE0))) 
  /*
  the above line of code is to make sure that 1 byte (or data) has finisehed proceesing before the next one arrives.
  we use UDRE0 (USART Data Register Empty) bit to control it.
  whenver this while function gives 0(this means the condition is false), it will moves to the next line of code
  look at it, "(1<<UDRE0)" is a constant. it's always 0010 0000.
  and UCSR0A can be 0010 0000 or 0000 0000. it's a variable

  when there is data inside, bit 5 (UDRE0) in UCSR0A is 0(low). that is 0000 0000
  when there is no data inside,bit 5 of UCSR0A is 1.that is 0010 0000

  so, to be able to wait for when there is no data inside the register.
  we must allows bit 5(UDRE0) of UCSR0A to go 1.

  how do we test that for that 1. we use bitwise logic.
  we can decide to check using "AND" oeprator between "(UCSR0A & (1<<UDRE0))" to check when it's high

or in this case, we want to make sure it's low (0).
remember we are testing for 0 or false here. if it's false,we can move to the next code
it works in this way:
        !(UCSR0A & (1<<UDRE0))  note that "!" is NOT  operator
  so, when UCSR0A is full(data is inside), it will be 0000 0000
  UCSR0A & UDRE0 will be :
  0000 0000  (UCSR0A has data inside)
            &
  0010 0000 (UDRE0)
  ---------
  0000 0000
  ---------
  Cargo is Full: The AND math equals 0 (False). You apply ! (NOT). !False becomes True (1). Because the condition is True, the while loop executes. It traps the CPU. It waits.

   now, when UCSR0A is empty(data is not inside), it will be 0010 0000
  UCSR0A & UDRE0 will be :
  0010 0000  (UCSR0A has no data inside)
            &
  0010 0000 (UDRE0)
  ---------
  0010 0000
  ---------
 Cargo is Empty: The AND math equals 32 (which C++ considers True because it is non-zero). You apply !. !True becomes False (0). Because the condition is now False, the while loop breaks, the CPU escapes, and drops the data into UDR0.

  */
  {
    //NOTHING
  }
  UDR0 = data;/*
  To send data out of the TX pin, you don't manipulate the pin directly. You simply drop an 8-bit variable into the USART I/O Data Register (UDR0).
The moment a byte hits this register, the UART hardware snatches it, breaks it down into individual bits, adds the Start and Stop bits, and fires it down the wire at 9600 bits per second.
  */
}

void uart_print_number(uint16_t num) {
  char buffer[5];
  int index = 0;

  if (num == 0) {
    uart_transmit('0');
    return;
  }

  while (num > 0)
  {
    int modulo_remainder = num % 10;
    char equivalent_ASCII = modulo_remainder + '0';
    buffer[index] = equivalent_ASCII;
    index++;
    num = num/10;
  }

  for (int last_index = index - 1; last_index >= 0; last_index--) {
    uart_transmit(buffer[last_index]);
  }
  
  
}

void setup() {
  uart_init(103);

 ADMUX |= (1<<REFS0);/*
 The ADMUX (ADC Multiplexer Selection Register) is used to select the lowest and highest voltage. 
                    The max obtainable voltage is Vcc
  Also, there is an invisble code written here,which wasn't explicitly written, but the unwritten code is what helps us to choose which ADc pin we wnat.
  in this case, we want PIN A0 (note that there are 6 ADC pins on the nano)
  ANy of these ^ pins can be used for ADC.
  We are supposed to define what Pins we are using for the projec using the MUX table in the arduino datasheet
  But here it's not written cos, all MUX Pins are to be written to zero
  Due to the fact that on a default,arduino configure registers to ) automatically
  we did not need to define it.

  even if we define it, it's not an issue. The code is below:
  ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0));

  As, u can see the above code simply equate MUX3 to MUX0 as zero.
  THE analog pin used in this project is A0. THose MUXx bits are what define it.
  defing MUX3-MUX0 as zero, means we want to use A0 as the ADC pin.
 */ 
 ADCSRA |= (1<<ADEN);/*
 ACDSRA (ADC Control and Status Register A) is used to enable the ADC (THAT IS, IT TURNS ON THE ADC) IN THIS CODE
 */
 ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);/*
 We made ADIE(ADC INTERRUPTS ENABLE) pin to be 1 to enable interrupts for ADC. 
 The interrupts is for when the ADC conversion is done (it takes some clock cycles)
 And we want to read the values automatically, so we just enabled the interrupts for it.

sO, THE ADCSRA registers needs a freq between 50-200 Khz to operates smoothly over a 10bit resolution.(The ADC is a 10bit resolution register. Higher resolution means better conversion)
SO, we used ADPPS2:0 to select the prescaler we need. 
In this case,we needed a prescaler of 124,and from the table in the datasheet, we need ADPS2:0 to be 1
 */


}


void loop() {
  ADCSRA |= (1<<ADSC);//This is to start the conversion by enabling ADSC (ADC START CONVERSION). This does it just 1 time

  while(ADCSRA & (1<<ADSC)) //This while function runs as long as the ADC is converting.
  {
   
  }
     uint16_t sensor_val = ADC;//This gives the pure decimal equivalent of the ADC readings to sensor_val variable. we are not converting it into a form suitable for 8bit as in past project.
     uart_transmit('v');
    uart_transmit('a');
    uart_transmit('l');
    uart_transmit(':');
    uart_transmit(' ');
     uart_print_number(sensor_val);//so we dump the number we want the serial monitor to print. it has a limit of 65,535
     uart_transmit('\r'); // Push the cursor to the far left
     uart_transmit('\n'); // Drop down to the next line
     _delay_ms(100);//delay is to allow get 10 values in 1 sec. the delay is 100 millisec. and 1 sec is 1000 millisec,therefore we have 10 "100 millisec" in 1 sec. this gives us 10 values
}

int main (void) {
  setup();
  while ((1))
  {
    loop();
  }
  return 0;
}