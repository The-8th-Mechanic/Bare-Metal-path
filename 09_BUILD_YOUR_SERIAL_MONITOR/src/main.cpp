#include <avr/io.h>

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

void setup() {
uart_init(103);//setting up baud_calc
uart_transmit('O');//sending "o". note that what is dropped in the register is the binary of "o" gotten from ASCII
uart_transmit('K');//same thing as o
uart_transmit('\n');//new line
}

void loop() {

}


int main(void) {
  setup();//run setup once
  while (1)// this line of code helps to run loop for ever
  {
    loop();
  }
  return 0;
}
