/*
Arduino library for Opel/Vauxhall Triple Info Display (TID)
found for example on Astra G or Corsa C series

works with 10 characters display ONLY !!


Version 1.2

reworked timings, runs well on ATMEGA328p (i. e. arduino nano v3.0)
changed methods a bit, now you can address three different spaces, each one can roll with his own speed
by default all three spaces starts and stops at first character, so in the setup function (or anywhere, really) you should define them


---electrical wiring----
These connections refers to the 12 pin connector on the back of the 10 digit display (Astra G, Corsa C)

1   -> +12 V (15)
2   -> Radio/Date Switch (AA), +12V
3   -> +12 V (30)
4   -> nc
5   -> nc
6   -> ground (please connect also arduino ground to TID ground)
7   -> nc
8   -> nc
9   -> nc
10  -> SCL czerwono-br%
11  -> SDA czarno-br
12  -> MRQ szaro-br



*/



#ifndef TID_H
#define TID_H
 
#include <Arduino.h> 

#define tid_delay 150
#define delay_300 150
#define delay_100 100

class TID {
public:
        TID(byte sda, byte scl, byte mrq); 

		void display_message(String message, byte speed, byte spaceid); // speed = 1 -> min speed = 255 -> max | spaceid from 1 to 3
		void space1_init(byte start, byte stop); // 0 is the leftmost char, 7 the rightmost
		void space2_init(byte start, byte stop);
		void space3_init(byte start, byte stop);
		void clear_space(byte spaceid);		//clear a specific space
		void reset_pos(byte spaceid);		//makes a rolling text restart from the beginning but doesn't force a display update, so you won't see it's effect 
											//until the next display_message call with the same spaceid

		void display_symbol(byte symbo);
		void clear_symbol(byte symbo);
		void clear_all_symbols();
		void bargraph(byte level);  //uses the symbols on top to create a bargraph effect, from left (minimum) to right


		/*
		
		
		symbols mapping:

		DolbyC	symbo = 1
		DolbyB	symbo = 2
		AS		symbo = 3
		Cr		symbo = 4
		stereo	symbo = 5
		CD		symbo = 6
		RDS		symbo = 7
		CPS		symbo = 8
		[]		symbo = 9
		TP		symbo = 10
		.		symbo = 11


		*/

		
		
		
private:
		void tid_byte(byte data);
		void tid_data(byte data);
		void tid_address();
		void start_tid();
		void stop_tid();
		void symbol_assign (byte symbo, byte RW);
		void cycle(); //sends a whole writing cycle 
//private:
		byte _sda;
		byte _scl;
		byte _mrq;
		
		byte _space1start;
		byte _space1stop;
		unsigned long _space1timestamp;
		byte _incr1;
		byte _ad1;
		
		byte _space2start;
		byte _space2stop;
		unsigned long _space2timestamp;
		byte _incr2;
		byte _ad2;

		byte _space3start;
		byte _space3stop;
		unsigned long _space3timestamp;
		byte _incr3;
		byte _ad3;


		byte _SYMBOLS1;
		byte _SYMBOLS2;
		char _display[9];
		byte _old_bars;
};
#endif
