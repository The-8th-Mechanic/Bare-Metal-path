# BASIC PWM WITH AN LED

## HOW IT WORKS:

A microcontroller can only send 5v(i mean its max voltage) and 0v.It can't send a voltage that is inbetween.

So, how do we make the microcontroller ssent voltage that seems to be incrementally decreasing or increasing. We use what is called PWM. 
FUnny thing, is that the microcontroller doesn't send 4.5v, it simply plays a trick.

we are going to specifically focus on leds. we know that if we connect an led to a power source without breaks in between is will get very hot, and the life expectancy of the led will reduce.

so, to resolve the above issue, PWM was devised. it works by sending 5v thousands or millions of times in a second (that is, the led is turned on (5v) and off(0v) ). FUnny things is, our brain and eye cooperate with the flashing to deceives us that it is a constant currwent flowing through.

Before i dive more into the real-world explanation, i want to give some analogies/examples:
1. Imagine getting slapped(Not a big deal). When u get slapped, u will feel the sensation lingering on your skin for a while. 
Now, imagine getting slapped before the sensation goes away.Your brain will combine all the slaps which came at various time into a single continous sensation as the pain sensation did not fully go away before the next one arrives.
2. Now, in the above analogy, u can fully discern when the next slap came right? because there is quite a large noticeable time difference.
As, we all know the slap sensation is the highest at the moment of contact.
Now, imahgine the slaps are comming at a high frequency. like imagine at time (t)=o second, a person slap u, then he slap u again at t=0.000006 sec(6 microsceond), our brain which processes signals in millisceond would not have finished processing the first slap, before another one hits u.Now, all of these slaps will combine into a single sensation it will be like someone kept his palm on your face and is applying a lot of force, whereas in reality the person has been hitting your face and removing his hand all in microseconds. but ur rain could not proces it, it is too slow to catch up to the hand speed, so it simply combines everything into a single form, where the pain is simply at it highest. This is for full contact slaps

THIS ANALOGY IS FOR A LED THAT IS LIGHT SEEMS SOLID, NOT BLINKING, OR DIMMING, JUST STATIC.

3.Now, imagine another scenario where u get slapped(Soory), at i said earlier, the pain is highest immediately u are hit (that is at time=0 seconds).but at time progresses, the pain reduces.

Now,look at this, if the person slap u but touches your skin in a time that is less than your skin can sense it, u will barely feel a thing regardless of it speed.but if the person increases the amount of time his hand stays onm your screen, u will gradually notice the pain sensation becomming stronger.
example: ur skin sensor processes signal at 0.1 secs, highest pain is when t= 1 sec
then at t=0.0001, u were touched, but ur skin will barely register anything. but when it get to 0.1 u will begin to fell the pain sensation, and at 0.1001,the pain is still negligible. 
the pain will increase at 0.101, the pain will still increase at 0.11,the pain keeps getting stronger the longer the time the hands stay on your face.
so, in essence, u are feeling an increase in intensity if the pain.

THIS ANALOGY WORKS FOR INCREASING LED BRIGHTNESS

3.let still go with, skin proceses pain at t=0.1 secs, and highest pain is at t=1 sec. so, let imagine the hand was on your face for 1 sec, then the next slap stays for 0.9 seconds and keep going down till 0.1, u will feel a decrease in pain signal.note that all of this is happening at high speed, and the time the hand stay is still constant.

THIS ANALOGY IS FOR  DIMMMING AN LED.



so, we got 3 separate analogies for PWM leds. 

LET ME EXPLAIN WITH LEDS AND EYES:
 
Look at this, when u see light that just turn on and off just once very fast , your brain will still have a lingering image of the light milliseconds after it's off. But, notes that the image disappears in your head at time progreses till it goes to 0.

Also, our eye and brain processes in milliseconds, therefore anything that is moving at microseconds will be like a blur (they can't be distinct because the input signal keeps overlapping. like the first signal enters the eye, before it has move, the next signal enter, the brain will simply combine everything into 1 entity).

Note, that the above analogy is to gives an intuitive understanding to the reader. You are expected to read more on PWM(Pulse Width Modulaion) and duty cycle.

This explanation of the code is in main,cpp. let go there

To get hiw bitwise operators works. Refer to project 1.