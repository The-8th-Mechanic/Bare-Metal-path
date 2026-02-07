## PROJECT NAME: 01_ignite 

# GOAL: To successfully blink an LED.

# UNDERSTANDING:
There are some registers in the ATMEGA328P chip, called DDRX.
Where "X" in DDRX, stands for B,C,D and if there are any other registers. The registers are named in this format,DDRB,DDRC OR DDRD.

Those DDRX registers are simply registers where you set the various pins that falls under these reigisters as INPUT or OUTPUT.

On a normal basis, the pins are always classified as INPUT, though i believe it won't do any harm to make it INPUT yourself to prevent future bugs.

Anyways, in this particular project we are only using the pins as OUTPUT.

How do we make them INPUT or OUTPUT, we simply equate the pin to 1 (for OUTPUT) or equate to 0 ( for INPUT)

Anyways, head over to main.cpp to understand further as we read the code and it comments.