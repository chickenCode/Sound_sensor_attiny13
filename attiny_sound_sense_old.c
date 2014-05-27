/*

    __//
    /.__.\         _     _      _               ██████╗ ██████╗ ██████╗ ███████╗
    \ \/ /        | |   (_)    | |             ██╔════╝██╔═══██╗██╔══██╗██╔════╝
 '__/    \     ___| |__  _  ___| | _ ___ _ __  ██║     ██║   ██║██║  ██║█████╗
  \-      )   / __| '_ \| |/ __| |/ / _ \ '_ \ ██║     ██║   ██║██║  ██║██╔══╝
   \_____/   | (__| | | | | (__|   <  __/ | | |╚██████╗╚██████╔╝██████╔╝███████╗
_____| |_     \___|_| |_|_|\___|_|\_\___|_| |_| ╚═════╝ ╚═════╝ ╚═════╝ ╚══════
     " "

Attiny13 Sound sensing code
This is the code for a device that senses sound levels and flashes LED's based on the sound.

Matt Permenter 2014
*/


#include <avr/io.h>

//dummy delay function
void delay()
{
    unsigned long int delayTime = 0;
    while(delayTime<=100000)
    {
     delayTime++;
    }
}

int main (void)
{
   DDRB |= (1 << PB4); // Set LED as output

   ADCSRA = (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Set ADC prescalar to 8

   ADMUX = (0 << REFS0); // Set ADC reference to VCC
   ADMUX |= (1 << ADLAR);
   ADMUX |= (1 << MUX1);  //mux 1 and 0 needed to be 11 to use ADC3
   ADMUX |= (1 << MUX0);

   ADCSRB = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);  // Set ADC to Free-Running Mode
   ADCSRA |= (1 << ADEN);  // Enable ADC
   ADCSRA |= (1 << ADATE);
   ADCSRA |= (1 << ADSC);  // Start A2D Conversions

   while(1)
   {
    if(ADCH > 128) //the higher this number goes the louder the sound will need to be
      {
         PORTB |= (1 << PB4); // Turn on LED
         delay();
         PORTB &= ~(1 << PB4); // Turn off LED
      }

      else
      {
         PORTB &= ~(1 << PB4); // Turn off LED
      }
   }
}
